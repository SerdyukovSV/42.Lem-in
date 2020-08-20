#include "../includes/lemin.h"

static void     enqueue(t_queue* queue, t_node *vert)
{
    // printf("enqueue\n");
    if (queue->rear == SIZE-1)
        ft_error(ERR);
    else
    {
        if(queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = vert;
    }
}

static t_node   *dequeue(t_queue* queue)
{
    // printf("\e[93mdequeue\e[0m\n");
    t_node *item;

    if (queue->rear == -1)
    {
        printf("\e[91mQueue is empty\e[0m");
        item = NULL;
    }
    else
    {
        item = queue->items[queue->front];
        queue->front++;
        if(queue->front > queue->rear)
        {
            queue->front = -1;
            queue->rear = -1;
        }
    }
    return (item);
}

static t_path   *reconstruct_path(t_lemin *lemin)
{
    // printf("reconstruct_path\n");
    t_path  *path;
    int     fin;

    if (!(path = malloc(sizeof(t_path))))
        return (NULL);
    fin = lemin->final;
    path->len = 0;
    path->node[path->len++] = lemin->node[fin];
    while (lemin->parent[fin] != -1)
    {
        fin= lemin->parent[fin];
        path->node[path->len++] = lemin->node[fin];
    }
    path->node[path->len] = NULL;
    return (path);
}

static void     add_queue(t_lemin *lemin, t_node *src, t_node *dst)
{
    // printf("\e[92madd_queue\e[0m\n");
    t_node **node;

    node = lemin->node;
    if (!node[src->id]->in_path)
    {
        if (node[dst->id]->in_path && !node[dst->id]->is_start)
        {
            enqueue(lemin->queue, node[node[dst->id]->previous]);
            lemin->links->visited[node[dst->id]->previous] = 1;
            lemin->parent[node[dst->id]->previous] = dst->id;
        }
        else if (!node[dst->id]->in_path)
            enqueue(lemin->queue, node[dst->id]);
        lemin->links->visited[dst->id] = 1;
        lemin->parent[dst->id] = src->id;
    }
    else if ((dst->capacity == 2 && dst->id != lemin->start) || (dst->capacity == 1 && !node[dst->id]->in_path))
    {
        enqueue(lemin->queue, node[dst->id]);
        lemin->links->visited[dst->id] = 1;
        lemin->parent[dst->id] = src->id;
    }
}

t_path          *search_path(t_lemin *lemin, t_node *src)
{
    // printf("search_path\n");
    t_node  *tmp;

    enqueue(lemin->queue, src);
    lemin->parent[src->id] = -1;
    while(lemin->queue->rear != -1)
    {
        src = dequeue(lemin->queue);
        lemin->links->visited[src->id] = 1;
        tmp = lemin->links->adjace[src->id];
        while(tmp)
        {
            if(lemin->links->visited[tmp->id] == 0)
            {
                if (tmp->id == lemin->final)
                {
                    lemin->parent[tmp->id] = src->id;
                    return (reconstruct_path(lemin));
                }
                add_queue(lemin, src, tmp);
            }
            tmp = tmp->next;
        }
    }
    return (NULL);
}
