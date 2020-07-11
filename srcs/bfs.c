#include "../includes/lemin.h"

static int  isEmpty(t_queue* queue)
{
    if(queue->rear == -1) 
        return 1;
    else 
        return 0;
}

void        bfs(t_lemin* lemin, t_links *link, int start)
{
    int         current;
    t_node      *adjacent;
    t_queue     *queue;
    int         parent[lemin->rooms->total];

    int i = -1;
    while (++i < lemin->rooms->total)
        link->visited[i] = 0;
    queue = creat_queue();
    enqueue(queue, start);
    parent[start] = -1;
    while(!isEmpty(queue))
    {
        current = dequeue(queue);
        link->visited[current] = 1;
        adjacent = link->adjace[current];
        while(adjacent)
        {
            if(link->visited[adjacent->id] == 0)
            {
                enqueue(queue, adjacent->id);
                link->visited[adjacent->id] = 1;
                parent[adjacent->id] = current;
            }
            adjacent = adjacent->next;
        }
    }
    if (lemin->size--)
        lem_get_paths(lemin, parent);
}
