#include "../includes/lemin.h"

static int      set_command(char *s, int pos)
{
    if (!ft_strcmp(s, "##start"))
        return (1);
    else if (!ft_strcmp(s, "##end"))
        return (2);
    return (pos);
}

static t_node *fill_room(t_node *room, char *str)
{
    char **tmp;

    if (!(tmp = ft_strsplit(str, ' ')))
        return (NULL);
    if (!(room->name = ft_strdup(tmp[0])))
        return (NULL);
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

static t_rooms *creat_room(t_rooms *rooms, char *str, int pos)
{
    t_node  *tmp;

    if (!(tmp = malloc(sizeof(t_node))))
        return (NULL);
    if (fill_room(tmp, str) == NULL)
        return (NULL);
    if (pos == 1)
        rooms->start = tmp;
    else if (pos == 2)
        rooms->end = tmp;
    tmp->next = rooms->head;
    rooms->head = tmp;
    rooms->total++;
    return (rooms);
}

t_rooms     *get_rooms(char ***str)
{
    t_rooms         *rooms;
    int             pos;

    if (!(rooms = malloc(sizeof(t_rooms))))
        return (NULL);
    pos = 0;
    rooms->total = 0;
    rooms->head = NULL;
    while (*(*str)++)
    {
        if ((*str)[0][0] == '#')
            pos = set_command((*str)[0], pos);
        else if (ft_wordcount((*str)[0], ' ') == 3)
        {
            if (creat_room(rooms, (*str)[0], pos) == NULL)
                return (NULL);
            pos = 0;
        }
        else
            break ;
    }
    return (rooms);
}