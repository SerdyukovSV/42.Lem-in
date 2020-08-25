#include "../includes/lemin.h"

t_node          *room_dup(t_node *room)
{
    t_node *cpy;

    if (!room)
        return (NULL);
    if (!(cpy = malloc(sizeof(t_node))))
        return (NULL);
    cpy->name = room->name;
    cpy->capacity = room->capacity;
    cpy->ant = room->ant;
    cpy->id = room->id;
    cpy->x = room->x;
    cpy->y = room->y;
    cpy->next = NULL;
    return (cpy);
}

static int      get_id(t_node *head, char *room)
{
    ///переделать head на tail т.к элементы идут с конца, большая потеря времени при переборе узлов
    while (head)
    {
        if (!ft_strcmp(room, head->name))
            return (head->id);
        head = head->next;
    }
    return (-1);
}

static t_links  *addlinks(t_links *links, t_node **node, int src, int dst)
{
    t_node *newroom;

    if ((newroom = room_dup(node[dst])) == NULL)
        return (NULL);
    newroom->next = links->adjace[src];
    links->adjace[src] = newroom;

    if ((newroom = room_dup(node[src])) == NULL)
        return (NULL);
    newroom->next = links->adjace[dst];
    links->adjace[dst] = newroom;
    return (links);
}

static t_links  *creat_links(t_lemin *lemin, char *str)
{
    int         id_room[2];
    char        **room;

    if ((room = ft_strsplit(str, '-')) == NULL)
        return (NULL);
    id_room[0] = get_id(lemin->rooms->head, room[0]);
    id_room[1] = get_id(lemin->rooms->head, room[1]);
    if (id_room[0] == -1 || id_room[1] == -1)
        ft_error(lemin, INVDLINK);
    if (!(addlinks(lemin->links, lemin->node, id_room[0], id_room[1])))
    {
        ft_matrix_del((void **)room);
        free(room);
        return (NULL);
    }
    ft_matrix_del((void **)room);
    free(room);
    return (lemin->links);
}

t_links *get_links(t_lemin *lemin, char **str)
{
    int size;

    size = lemin->rooms->total + 1;
    if (!(lemin->links = malloc(sizeof(t_links))))
        ft_error(lemin, ERR);
    if (!(lemin->links->adjace = malloc(sizeof(t_node *) * size)))
        ft_error(lemin, ERR);
    ft_bzero(lemin->links->adjace, sizeof(t_node *) * size);
    while (str[lemin->count])
    {
        if (is_command(str[lemin->count]))
            ;
        else if (is_link(str[lemin->count]))
        {
            if (!creat_links(lemin, str[lemin->count]))
                ft_error(lemin, ERR);
        }
        else
            break ;
        lemin->count++;
    }
    return (lemin->links);
}