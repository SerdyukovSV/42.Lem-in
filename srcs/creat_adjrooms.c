#include "../includes/lemin.h"

static t_node   *room_cpy(t_node *room)
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
    while (head)
    {
        if (!ft_strcmp(room, head->name))
            return (head->id);
        head = head->next;
    }
    return (-1);
}

static void     addlinks(t_adjacent *adj, int src, int dst)
{
    t_node *newroom;

    // newroom = room_cpy(adj->rooms[dst]);
    // newroom->next = adj->adjrooms[src];
    // adj->adjrooms[src] = newroom;

    // newroom = room_cpy(adj->rooms[src]);
    // newroom->next = adj->adjrooms[dst];
    // adj->adjrooms[dst] = newroom;
}

void            creat_links(t_node *head, t_adjacent *adj, char *line[])
{
    int         id_room[2];
    char        **link;

    if (!ft_strchr(line[0], '-') || ft_wordcount(line[0], 32) != 1)
        ft_error(INVDLINK);
    link = ft_strsplit(line[0], '-');
    id_room[0] = get_id(head, link[0]);
    id_room[1] = get_id(head, link[1]);
    if (id_room[0] == -1 || id_room[1] == -1)
        ft_error(INVDLINK);
    addlinks(adj, id_room[0], id_room[1]);
    lm_strdel(link);
}