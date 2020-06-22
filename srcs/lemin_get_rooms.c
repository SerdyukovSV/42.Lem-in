#include "../includes/lemin.h"

static void lm_fill_room(t_node *room, char *line[])
{
    char **tmp;

    if ((tmp = ft_strsplit(line[0], 32)) == NULL)
        ft_error(ERR);
    room->name = ft_strdup(tmp[0]);
    room->x = ft_atoi(tmp[1]);
    room->y = ft_atoi(tmp[2]);
    room->id = g_id++;
    lm_strdel(tmp);
}

static void lm_creat_room(t_rooms *rooms, char *line[], int pos)
{
    t_node  *tmp;

    if (!(tmp = malloc(sizeof(t_node))))
        ft_error(ERR);
    lm_fill_room(tmp, line);
    if (pos == 1) rooms->start = tmp;
    if (pos == 2) rooms->end = tmp;
    tmp->next = rooms->head;
    rooms->head = tmp;
    rooms->total += 1;
}

void        lemin_get_rooms(int fd, char *line[], t_rooms *rooms)
{
    int    pos;

    pos = 0;
    g_id = 0;
    rooms->head = NULL;
    while (get_next_line(fd, &line[0]) > 0)
    {
        if (**line == '#')
        {
            if ((*line)[2] == 's') pos = 1;
            if ((*line)[2] == 'e') pos = 2;
            continue;
        }
        if (ft_wordcount(line[0], 32) == 3)
        {
            lm_creat_room(rooms, line, pos);
            if (pos) pos = 0;
            free(line[0]);
        }
        else
            break;
    }
}