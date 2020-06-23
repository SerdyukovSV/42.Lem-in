#include "../includes/lemin.h"

static int  isEmpty(t_queue* queue)
{
    if(queue->rear == -1) 
        return 1;
    else 
        return 0;
}

void        breadth_first_search(t_lemin* farm, t_adjrms *adj, int start)
{
    int         current;
    t_node      *adjroom;
    t_queue     *queue;

    queue = creat_queue();
    enqueue(queue, start);
    push_path(&farm->parent[start], -1);
    while(!isEmpty(queue))
    {
        current = dequeue(queue);
        adj->visited[current] = 1;
        adjroom = adj->adjrooms[current];
        while(adjroom)
        {
            if(adj->visited[adjroom->id] == 0)
            {
                enqueue(queue, adjroom->id);
                adj->visited[adjroom->id] = -1;
                push_path(&farm->parent[adjroom->id], current);
            }
            else if (adj->visited[adjroom->id] == -1)
                push_path(&farm->parent[adjroom->id], current);
            adjroom = adjroom->next;
        }
    }
}

    // int i = 0;
    // while (i < farm->rooms->total)
    // {
    //     printf("[%s]", farm->adjrms->rooms[i]->name);
    //     if (farm->parent[i]->room != -1)
    //         printf("->%s", farm->adjrms->rooms[farm->parent[i]->room]->name);
    //     farm->parent[i] = farm->parent[i]->next;
    //     while (farm->parent[i])
    //     {
    //         if (farm->parent[i]->room != -1)
    //         printf("->%s", farm->adjrms->rooms[farm->parent[i]->room]->name);
    //         farm->parent[i] = farm->parent[i]->next;
    //     }
    //     printf("\n");
    //     i++;
    // }