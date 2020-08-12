#include "../includes/lemin.h"

void    enqueue(t_queue* queue, int value)
{
    if (queue->rear == SIZE-1)
        ft_error(ERR);
    else
    {
        if(queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

int     dequeue(t_queue* queue)
{
    int item;
    if (queue->rear == -1)
    {
        printf("Queue is empty");
        item = -1;
    }
    else
    {
        item = queue->items[queue->front];
        queue->front++;
        if(queue->front > queue->rear)
            queue->front = queue->rear = -1;
    }
    return item;
}

t_queue *creat_queue(void)
{
    t_queue *queue;

    if (!(queue = malloc(sizeof(t_queue))))
        ft_error(ERR);
    queue->front = -1;
    queue->rear = -1;

    return (queue);
}