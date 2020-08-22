#include "../includes/lemin.h"

t_node   *room_dup(t_node *room)
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

static void     *addlinks(t_links *links, t_node **node, int src, int dst)
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
    return ((t_links *)links);
}

static void     *creat_links(t_lemin *lemin, t_links *links, char *str)
{
    int         id_room[2];
    char        **room;

    if ((room = ft_strsplit(str, '-')) == NULL)
        return (NULL);
    id_room[0] = get_id(lemin->rooms->head, room[0]);
    id_room[1] = get_id(lemin->rooms->head, room[1]);
    if (!(addlinks(links, lemin->node, id_room[0], id_room[1])))
    {
        lm_strdel(room);
        free(room);
        return (NULL);
    }
    lm_strdel(room);
    free(room);
    return ((t_links *)links);
}

t_links *get_links(t_lemin *lemin, char **str)
{
    t_links    *links;

    if (!(links = malloc(sizeof(t_links))))
        return (NULL);
    if (!(links->adjace = malloc(sizeof(t_node *) * (lemin->rooms->total + 1))))
        return (NULL);
    ft_bzero(links->adjace, sizeof(t_node *) * lemin->rooms->total + 1);
    while (str[0])
    {
        if (str[0][0] != '#')
            if (creat_links(lemin, links, str[0]) == NULL)
                return (NULL);
        str++;
    }
    return (links);
}