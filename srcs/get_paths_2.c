#include "../includes/lemin.h"

static void del_link(t_links *link, t_node *path)
{
    t_node *tmp;
    t_node *tmp2;
    t_node *adj;

    while (path->next)
    {
        adj = link->adjace[path->id];   //возвращаю смежные вершины 1-го узла маршрута
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
        path = path->next;
    }
}

static void add_path(t_lemin *lemin, int *parent, int final)
{
    t_node      *tmp;
    t_node      **paths;
    t_node      **rooms;

    paths = lemin->paths;
    rooms = lemin->rooms->hroom;
    paths[lemin->count] = room_dup(rooms[final]);
    while (parent[final] != -1)
    {
        tmp = room_dup(rooms[parent[final]]);
        tmp->next = paths[lemin->count];
        paths[lemin->count] = tmp;
        final = parent[final];
    }
    del_link(lemin->links, paths[lemin->count++]->next);
}

static void search_path(t_links *link, t_queue *queue, int *parent, int cur)
{
    t_node      *tmp;

    enqueue(queue, cur);
    parent[cur] = -1;
    while(queue->rear != -1)
    {
        cur = dequeue(queue);
        link->visited[cur] = 1;
        tmp = link->adjace[cur];
        while(tmp)
        {
            if(link->visited[tmp->id] == 0)
            {
                enqueue(queue, tmp->id);
                link->visited[tmp->id] = 1;
                parent[tmp->id] = cur;
            }
            tmp = tmp->next;
        }
    }
}

void    get_paths(t_lemin* lemin)
{
    printf("\e[92mget_paths\e[0m\n");
    int parent[lemin->rooms->total];
    int total;
    int start;
    int final;

    total = lemin->rooms->total;
    start = lemin->rooms->start->id;
    final = lemin->rooms->end->id;
    while (lemin->count < lemin->size)
    {
        ft_bzero(parent, sizeof(int) * total);
        ft_bzero(lemin->links->visited, sizeof(int) * total);
        search_path(lemin->links, creat_queue(), parent, start);
        if (!lemin->links->visited[final])
            break ;
        add_path(lemin, parent, final);
    }
}