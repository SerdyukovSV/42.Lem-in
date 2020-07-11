#include "../includes/lemin.h"

t_node   *room_dup(t_node *room)
{
    t_node *cpy;

    if (!room)
        return (NULL);
    if (!(cpy = malloc(sizeof(t_node))))
        ft_error(ERR);
    cpy->id = room->id;
    cpy->name = room->name;
    cpy->next = NULL;
    cpy->x = room->x;
    cpy->y = room->y;
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

static void     addlinks(t_links *link, t_rooms *rooms, int src, int dst)
{
    t_node *newroom;

    newroom = room_dup(rooms->hroom[dst]);
    newroom->next = link->adjace[src];
    link->adjace[src] = newroom;

    newroom = room_dup(rooms->hroom[src]);
    newroom->next = link->adjace[dst];
    link->adjace[dst] = newroom;
}

static void     creat_links(t_rooms *rooms, t_links *link, char *str)
{
    int         id_room[2];
    char        **room;

    room = ft_strsplit(str, '-');
    id_room[0] = get_id(rooms->head, room[0]);
    id_room[1] = get_id(rooms->head, room[1]);
    if (id_room[0] == -1 || id_room[1] == -1)
        ft_error(INVDLINK);
    addlinks(link, rooms, id_room[0], id_room[1]);
    lm_strdel(room);
}

t_links *get_links(t_rooms *rooms, char **str)
{
    t_links    *link;
    int         i;

    i = -1;
    if (!(link = malloc(sizeof(t_links))))
        return (NULL);
    if (!(link->adjace = malloc(sizeof(t_node *) * rooms->total)))
        return (NULL);
    if (!(link->visited = malloc(sizeof(int) * rooms->total)))
        return (NULL);
    while (++i < rooms->total)
    {
        link->adjace[i] = NULL;
        link->visited[i] = 0;
    }
    while (str[0])
    {
        if (str[0][0] != '#')
            creat_links(rooms, link, str[0]);
        str++;
    }
    return (link);
}