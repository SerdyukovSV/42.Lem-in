#include "../includes/lemin.h"

static int  isEmpty(t_queue* queue)
{
    if(queue->rear == -1) 
        return 1;
    else 
        return 0;
}

// static int  delete_link(t_links *link, int start, int delete)
// {
//     t_node *tmp;

//     tmp = link->adjace[start];
//     if (tmp && tmp->id == delete)
//     {
//         link->adjace[start] = tmp->next;
//         if (!link->adjace[start])
//             return (0);
//         return (1);
//     }
//     else
//     {
//         while (tmp)
//         {
//             if (tmp->next->id == delete)
//             {
//                 tmp->next = tmp->next->next;
//                 return (1);
//             }
//             tmp = tmp->next;
//         }
//     }
//     return (0);
// }

void print_lst(t_node *path, t_links *link)
{
    t_node *tmp;

    while (path)
    {
        tmp = link->adjace[path->id];
        printf("\e[92madj[%s] = ", path->name);
        while (tmp)
        {
            printf("->%s", tmp->name);
            tmp = tmp->next;
        }
        path = path->next;
        printf("\e[0m\n");
    }
    printf("\e[0m\n");
}

static void  delete_link_2(t_links *link, t_node *path)
{
    // printf("\e[91mdelete_link_2\e[0m\n");
    t_node *tmp;
    t_node *tmp2;
    t_node *adj;

    while (path->next)
    {
        adj = link->adjace[path->id];   //возвращаю смежные вершины 1-го узла маршрута
        // print_lst(link->adjace[path->id], link);
        while (adj)
        {
            tmp = link->adjace[adj->id];    //перебираю смежыне вершины 1-го узла и удалаю ссылки на текущую вершину
            if (link->adjace[adj->id]->id == path->id)
            {
                if (link->adjace[adj->id]->next)
                {
                    link->adjace[adj->id] = link->adjace[adj->id]->next;
                    free(tmp);
                }
            }
            else
            {
                while (tmp->next && tmp->next->id != path->id)
                    tmp = tmp->next;
                if (tmp->next && tmp->next->id == path->id)
                {
                    tmp2 = tmp->next;
                    tmp->next = tmp->next->next;
                    free(tmp2);
                }
            }
            adj = adj->next;
        }
        // print_lst(link->adjace[path->id], link);
        // printf("------------------------------\n");
        path = path->next;
    }
}

static void add_path(t_lemin *lemin, int *parent)
{
    // printf("\e[91madd_path\e[0m\n");
    t_node      *tmp;
    // int         start;
    int         fin;

    fin = lemin->rooms->end->id;
    // start = lemin->rooms->start->id;
    if (!lemin->links->visited[fin])
        return ;
    lemin->paths[lemin->count] = room_dup(lemin->rooms->hroom[fin]);
    while (parent[fin] != -1)
    {
        tmp = room_dup(lemin->rooms->hroom[parent[fin]]);
        tmp->next = lemin->paths[lemin->count];
        lemin->paths[lemin->count] = tmp;
        fin = parent[fin];
    }
    delete_link_2(lemin->links, lemin->paths[lemin->count++]->next);
    if (lemin->count < lemin->size)
        get_paths(lemin, lemin->links, lemin->rooms->start->id);
}

void        get_paths(t_lemin* lemin, t_links *link, int start)
{
    // printf("\e[91mget_paths\e[0m\n");
    t_node      *adjacent;
    int         parent[lemin->rooms->total];

    ft_bzero(link->visited, sizeof(int) * lemin->rooms->total);
    ft_bzero(parent, sizeof(int) * lemin->rooms->total);
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
    add_path(lemin, parent);
}
