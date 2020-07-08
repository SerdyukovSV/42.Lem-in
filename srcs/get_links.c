#include "../includes/lemin.h"

void            create_adjrooms(t_rooms *rm, t_adjacent *adj)
{
    t_node *tmp;

    adj->adjacent = malloc(sizeof(t_node *) * rm->total);
    // adj->rooms = malloc(sizeof(t_node *) * rm->total);
    adj->visited = malloc(sizeof(int) * rm->total);
    if (!(adj->adjacent || /* adj->rooms || */ adj->visited))
        ft_error(ERR);
    tmp = rm->head;
    while (tmp)
    {
        adj->adjacent[tmp->id] = NULL;
        // adj->rooms[tmp->id] = tmp;
        adj->visited[tmp->id] = 0;
        tmp = tmp->next;
    }
}

void    get_links(t_lemin *lemin, char *str[])
{
    t_adjacent    adjacent;
    int         i;

    i = 0;
    // adjacent.
    create_adjrooms(lemin->rooms, &adjacent);
    while (str[i])
    {
        // if (str[0] == '#')
            // continue;
        creat_links(lemin->rooms->head, &adjacent, str);
    }
    lemin->adjrms = &adjacent;
}