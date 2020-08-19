#include "../includes/lemin.h"

void    enqueue(t_queue* queue, t_node *vert)
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

t_node  *dequeue(t_queue* queue)
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