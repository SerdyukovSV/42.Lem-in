#include "../includes/lemin.h"

static int      set_command(t_rooms *rooms, int ret)
{
    if ((ret == START && rooms->start) || (ret == END && rooms->end))
        return (DUPCOMM);
    rooms->pos = ret;
    return (ret);
}

static t_node   *fill_room(t_node *room, char *str)
{
    char **tmp;

    if (!(tmp = ft_strsplit(str, ' ')))
        return (NULL);
    if (!(room->name = ft_strdup(tmp[0])))
    {
        ft_matrix_del((void **)tmp);
        free(tmp);
        return (NULL);
    }
    room->x = ft_atoi(tmp[1]);
    room->y = ft_atoi(tmp[2]);
    room->ant = 0;
    room->capacity = 1;
    room->is_start = 0;
    room->in_path = 0;
    room->id = g_id++;
    ft_matrix_del((void **)tmp);
    free(tmp);
    tmp = NULL;
    return (room);
}

static t_rooms  *creat_room(t_rooms *rooms, char *str)
{
    t_node  *tmp;

    if (!(tmp = malloc(sizeof(t_node))))
        return (NULL);
    if (fill_room(tmp, str) == NULL)
    {
        free(tmp);
        return (NULL);
    }
    if (rooms->pos == START)
        rooms->start = tmp;
    else if (rooms->pos == END)
        rooms->end = tmp;
    tmp->next = rooms->head;
    rooms->head = tmp;
    rooms->total++;
    rooms->pos = 0;
    return (rooms);
}

static void     init_rooms(t_rooms *rooms)
{
    rooms->head = NULL;
    rooms->start = NULL;
    rooms->end = NULL;
    rooms->total = 0;
    rooms->pos = 0;
}

t_rooms         *get_rooms(t_lemin *lemin, char **str)
{
    int ret;

    if (!(lemin->rooms = malloc(sizeof(t_rooms))))
        ft_error(lemin, ERR);
    init_rooms(lemin->rooms);
    while (str[++lemin->count])
    {
        if ((ret = is_command(str[lemin->count])))
        {
            if (set_command(lemin->rooms, ret) == DUPCOMM)
                ft_error(lemin, DUPCOMM);
        }
        else if (is_room(str[lemin->count]))
        {
            if (!creat_room(lemin->rooms, str[lemin->count]))
                ft_error(lemin, ERR);
        }
        else
            break ;
    }
    return (lemin->rooms);
}