#include "../includes/lemin.h"

static void     search_path(t_lemin *lem, t_queue *queue, int *parent, int current)
{
    t_node      *tmp;

    ft_bzero(parent, sizeof(int) * lem->rooms->total);
    enqueue(queue, current);
    parent[current] = -1;
    while(queue->rear != -1)
    {
        current = dequeue(queue);
        lem->links->visited[current] = 1;
        tmp = lem->links->adjace[current];
        while(tmp)
        {
            if (tmp->path == 0)
            {
                if(lem->links->visited[tmp->id] == 0)
                {
                    enqueue(queue, tmp->id);
                    lem->links->visited[tmp->id] = 1;
                    parent[tmp->id] = current;
                }
            }
            tmp = tmp->next;
        }
    }
}

void            get_paths(t_lemin* lemin)
{
    int     parent[lemin->rooms->total];
    t_node  *start;
}
