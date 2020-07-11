#include "../includes/lemin.h"

static int delete_link(t_links *link, int start, int delete)
{
    t_node *tmp;

    tmp = link->adjace[start];
    if (tmp && tmp->id == delete)
    {
        link->adjace[start] = tmp->next;
        if (!link->adjace[start])
            return (0);
        return (1);
    }
    else
    {
        while (tmp)
        {
            if (tmp->next->id == delete)
            {
                tmp->next = tmp->next->next;
                return (1);
            }
            tmp = tmp->next;
        }
    }
    return (0);
}

void        lem_get_paths(t_lemin *lemin, int *parent)
{
    t_node      *tmp;
    int         start;
    int         fin;

    printf("count = %d\n", lemin->count);
    fin = lemin->rooms->end->id;
    start = lemin->rooms->start->id;
    if (!lemin->links->visited[fin])
        ft_error(NOPATH);
    lemin->paths[lemin->count] = room_dup(lemin->rooms->hroom[fin]);
    while (parent[fin] != -1)
    {
        tmp = room_dup(lemin->rooms->hroom[parent[fin]]);
        tmp->next = lemin->paths[lemin->count];
        lemin->paths[lemin->count] = tmp;
        fin = parent[fin];
    }
    if (delete_link(lemin->links, start, lemin->paths[lemin->count++]->next->id))
        bfs(lemin, lemin->links, lemin->rooms->start->id);
}
