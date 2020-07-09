#include "../includes/lemin.h"

static void create_hash_room(t_rooms *room)
{
    t_node **hash;
    t_node *head;

    head = room->head;
    if (!(hash = malloc(sizeof(t_node *) * room->total)))
        ft_error(ERR);
    while (head)
    {
        hash[head->id] = head;
        head = head->next;
    }
    room->hroom = hash;
}

static void fill_room(t_node *room, char *str)
{
    char **tmp;

    if (!(tmp = ft_strsplit(str, ' ')))
        ft_error(ERR);
    room->name = ft_strdup(tmp[0]);
    room->x = ft_atoi(tmp[1]);
    room->y = ft_atoi(tmp[2]);
    room->id = g_id++;
    lm_strdel(tmp);
}

static void creat_room(t_rooms *rooms, char *str, int pos)
{
    t_node  *tmp;

    if (!(tmp = malloc(sizeof(t_node))))
        ft_error(ERR);
    fill_room(tmp, str);
    (pos == 1) ? (rooms->start = tmp) : 0;
    (pos == 2) ? (rooms->end = tmp) : 0;
    tmp->next = rooms->head;
    rooms->head = tmp;
    rooms->total++;
}

t_rooms     *get_rooms(char ***str)
{
    t_rooms         *rooms;
    int             pos;

    if (!(rooms = malloc(sizeof(t_rooms))))
        ft_error(ERR);
    pos = 0;
    rooms->total = 0;
    rooms->head = NULL;
    while (*(*str)++)
    {
        if ((*str)[0][0] == '#')
        {
            if ((*str)[0][1] == '#')
                pos = (*str)[0][2] == 's' ? 1 : 2;
        }
        else if (ft_wordcount((*str)[0], ' ') == 3)
        {
            creat_room(rooms, (*str)[0], pos);
            pos = 0;
        }
        else
            break ;
    }
    create_hash_room(rooms);
    return (rooms);
}