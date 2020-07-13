#include "../includes/lemin.h"

static int  isEmpty(t_queue* queue)
{
    if(queue->rear == -1) 
        return 1;
    else 
        return 0;
}

static int  delete_link(t_links *link, int start, int delete)
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

static void add_path(t_lemin *lemin, int *parent)
{
    t_node      *tmp;
    int         start;
    int         fin;

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
        get_paths(lemin, lemin->links, lemin->rooms->start->id);
}

void        get_paths(t_lemin* lemin, t_links *link, int start)
{
    t_node      *adjacent;
    int         parent[lemin->rooms->total];

    ft_bzero(link->visited, sizeof(parent));
    lemin->queue = creat_queue();
    enqueue(lemin->queue, start);
    parent[start] = -1;
    while(!isEmpty(lemin->queue))
    {
        start = dequeue(lemin->queue);
        link->visited[start] = 1;
        adjacent = link->adjace[start];
        while(adjacent)
        {
            if(link->visited[adjacent->id] == 0)
            {
                enqueue(lemin->queue, adjacent->id);
                link->visited[adjacent->id] = 1;
                parent[adjacent->id] = start;
            }
            adjacent = adjacent->next;
        }
    }
    if (lemin->count < lemin->size)
        add_path(lemin, parent);
}
