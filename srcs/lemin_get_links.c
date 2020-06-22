#include "../includes/lemin.h"

void    lemin_get_links(int fd, char *line[], t_lemin *lem)
{
    t_adjrms    *adj;

    if (!(adj = malloc(sizeof(t_adjrms))))
        ft_error(ERR);
    create_adjrooms(lem->rooms, adj);
    if (line[0])
    {
        creat_links(lem->rooms->head, adj, line);
        free(line[0]);
    }
    while (get_next_line(fd, &line[0]) > 0)
    {
        if ((*line)[0] == '#')
            continue;
        creat_links(lem->rooms->head, adj, line);
        free(line[0]);
    }
    lem->adjrms = adj;
}

// int i = 0;
    // while (i < rms->total_rooms)
    // {
    //     printf("%s", adj->rooms[i]->name);
    //     while (adj->adjrooms[i])
    //     {
    //         printf("->%s", adj->adjrooms[i]->name);
    //         adj->adjrooms[i] = adj->adjrooms[i]->next;
    //     }
    //     printf("\n");
    //     i++;
    // }