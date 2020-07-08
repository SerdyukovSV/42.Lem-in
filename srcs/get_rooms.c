#include "../includes/lemin.h"

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

t_rooms     *get_rooms(char *str[])
{
    static t_rooms  rooms;
    int             pos;

    pos = 0;
    rooms.head = NULL;
    while (*(str++))
    {
        if (str[0][0] == '#')
        {
            if (str[0][1] == '#')
            {
                str[0][2] == 's' ? (pos = 1) : 0;
                str[0][2] == 'e' ? (pos = 2) : 0;
                !pos ? ft_error(ERR) : 0;
            }
        }
        else if (ft_wordcount(str[0], ' ') == 3)
        {
            creat_room(&rooms, str[0], pos);
            pos = 0;
        }
        else
            break ;
    }
    return (&rooms);
}