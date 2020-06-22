#include "../includes/lemin.h"

void    lm_strdel(char **str)
{
    while (*str != NULL)
    {
        ft_strdel(&(*str));
        str += 1;
    }
}

t_lemin *lemin_init(int fd)
{
    char    *line;
    t_lemin *lemin;

    if (!(lemin = malloc(sizeof(t_lemin))))
        ft_error(ERR);
    lemin->ants = lemin_get_ants(fd);
    if (!(lemin->rooms = malloc(sizeof(t_rooms))))
        ft_error(ERR);
    lemin_get_rooms(fd, &line, lemin->rooms);
    lemin_get_links(fd, &line, lemin);

    return (lemin);
}


    // printf("ants = %d\n", lemin->ants);
    // printf("start [%s : %d] coord [%d][%d]\n", lemin->rooms->start->name, lemin->rooms->start->id, lemin->rooms->start->x, lemin->rooms->start->y);
    // printf("end [%s : %d] coord [%d][%d]\n", lemin->rooms->end->name, lemin->rooms->end->id, lemin->rooms->end->x, lemin->rooms->end->y);
    // while (lemin->rooms->head)
    // {
    //     printf("name/id [%s : %d] coord [%d][%d]\n", lemin->rooms->head->name, lemin->rooms->head->id, lemin->rooms->head->x, lemin->rooms->head->y);
    //     lemin->rooms->head = lemin->rooms->head->next;
    // }
    // printf("total_rooms = %d\n", lemin->rooms->total_rooms);