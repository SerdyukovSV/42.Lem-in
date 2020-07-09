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

    queue = creat_queue();
    enqueue(queue, start);
    push_path(&lemin->parent[start], -1);
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
                link->visited[adjacent->id] = -1;
                push_path(&lemin->parent[adjacent->id], current);
            }
            else if (link->visited[adjacent->id] == -1)
                push_path(&lemin->parent[adjacent->id], current);
            adjacent = adjacent->next;
        }
    }
    int i = -1;
    while (++i < lemin->rooms->total)
    {
        printf("[%s]", lemin->rooms->hroom[i]->name);
        if (lemin->parent[i]->room == -1)
            printf("->(%d)", lemin->parent[i]->room);
        while (lemin->parent[i] && lemin->parent[i]->room != -1)
        {
            printf("->%s", lemin->rooms->hroom[lemin->parent[i]->room]->name);
            lemin->parent[i] = lemin->parent[i]->next;
        }
        printf("\n");
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