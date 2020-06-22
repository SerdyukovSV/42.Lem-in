#include "../includes/lemin.h"

int     adj_length(t_adjrms *adj, int room)
{
    t_node  *tmp;
    int     len;

    len = 0;
    tmp = adj->adjrooms[room];
    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }
    return (len);
}

void    add_path(t_path **path, int room)
{
    t_path *tmp;

    if (!(tmp = malloc(sizeof(t_path))))
        ft_error(ERR);
    tmp->room = room;
    tmp->next = *path;
    *path = tmp;
}

t_path  **creat_paths(t_adjrms *adj, int len)
{
    t_path  **path;
    int     i;

    if (!(path = malloc(sizeof(t_path *) * len)))
        ft_error(ERR);
    i = -1;
    while (++i < len)
        path[i] = NULL;
    return (path);
}

t_path  **lemin_get_paths(t_lemin *lem, t_adjrms *adj, int parent[])
{
    t_path  **paths;
    int     final;
    int     len;
    int     tmp;
    int     i;

    len = adj_length(adj, lem->rooms->end->id);
    paths = creat_paths(adj, len);

    final = lem->rooms->end->id;
    if (!adj->visited[final])
        ft_error("No paths");
    i = 0;
    while (i < len)
    {
        add_path(&paths[i], final);
        tmp = adj->adjrooms[final]->id;
        while (tmp != -1)
        {
            add_path(&paths[i], tmp);
            tmp = parent[tmp];
        }
        adj->adjrooms[final] = adj->adjrooms[final]->next;
        i++;
    }
    i = 0;
    printf("len = %d\n", len);
    while (i < len)
    {
        printf("Path[%d] : %s", i, adj->rooms[paths[i]->room]->name);
        paths[i] = paths[i]->next;
        while (paths[i])
        {
            printf("->%s", adj->rooms[paths[i]->room]->name);
            paths[i] = paths[i]->next;
        }
        i++;
        printf("\n");
    }
    return (paths);
}

int isEmpty(t_queue* queue)
{
    if(queue->rear == -1) 
        return 1;
    else 
        return 0;
}

void breadth_first_search(t_lemin* farm, t_adjrms *adj, int start)
{
    int         parent[farm->rooms->total];
    int         current;
    t_node      *adjroom;
    t_queue     *queue;

    queue = creat_queue();
    enqueue(queue, start);
    adj->visited[start] = 1;
    parent[start] = -1;
    while(!isEmpty(queue))
    {
        current = dequeue(queue);
        printf("Visited %d\n", current);
       adjroom = adj->adjrooms[current];
       while(adjroom)
       {
            if(adj->visited[adjroom->id] == 0)
            {
                adj->visited[adjroom->id] = 1;
                enqueue(queue, adjroom->id);
                parent[adjroom->id] = current;
            }
            adjroom = adjroom->next;
       }
    }
    lemin_get_paths(farm, farm->adjrms, parent);
}