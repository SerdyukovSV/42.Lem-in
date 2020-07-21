#include "../includes/lemin.h"

static int  del_set_link(t_links *links, t_node *node, int final, int set)
{
    // printf("del_set_link\n");
    t_node  *tmp_p;
    t_node  *tmp_l;
    int     ret;

    ret = 0;
    if (node && node->id != final)
    {
        tmp_p = links->adjace[node->id];
        while (tmp_p)
        {
            tmp_l = links->adjace[tmp_p->id];
            while (tmp_l && tmp_l->id != node->id)
                tmp_l = tmp_l->next;
            if (tmp_l->id == node->id)
            {
                tmp_l->path = set;
                ret = 1;
            }
            tmp_p = tmp_p->next;
        }
    }
    return (ret);
}

static void add_path(t_lemin *lemin, int *parent, int final)
{
    t_node      *tmp;
    t_node      **paths;
    t_node      **rooms;

    paths = lemin->paths;
    rooms = lemin->rooms->hroom;
    if (!lemin->links->visited[final])
        return ;
    paths[lemin->count] = room_dup(rooms[final]);
    while (parent[final] != -1)
    {
        tmp = room_dup(rooms[parent[final]]);
        tmp->next = paths[lemin->count];
        paths[lemin->count] = tmp;
        final = parent[final];
    }
    lemin->count++;
}

static void search_path(t_lemin *lem, t_queue *queue, int *parent, int cur)
{
    t_node      *tmp;

    ft_bzero(lem->links->visited, sizeof(int) * lem->rooms->total);
    ft_bzero(parent, sizeof(int) * lem->rooms->total);
    enqueue(queue, cur);
    parent[cur] = -1;
    while(queue->rear != -1)
    {
        cur = dequeue(queue);
        lem->links->visited[cur] = 1;
        tmp = lem->links->adjace[cur];
        while(tmp)
        {
            if (tmp->path == 0)
            {
                if(lem->links->visited[tmp->id] == 0)
                {
                    enqueue(queue, tmp->id);
                    lem->links->visited[tmp->id] = 1;
                    parent[tmp->id] = cur;
                }
            }
            tmp = tmp->next;
        }
    }
}

static void adjacent_paths(t_lemin *lemin, t_node *path, int start, int final)
{
    int     parent[lemin->rooms->total];
    t_node  *tmp;

    tmp = path->next;
    path = path->next;
    while (del_set_link(lemin->links, path, final, 1))
    {
        search_path(lemin, creat_queue(), parent, start);
        add_path(lemin, parent, final);
        del_set_link(lemin->links, path, final, 0);
        path = path->next;
    }
    while (tmp)
    {
        del_set_link(lemin->links, tmp, final, 1);
        tmp = tmp->next;
    }
}

void        get_paths(t_lemin* lemin)
{
    int parent[lemin->rooms->total];
    int start;
    int final;
    int i;

    i = 0;
    final = lemin->rooms->end->id;
    start = lemin->rooms->start->id;
    while (i < lemin->size)
    {
        search_path(lemin, creat_queue(), parent, start);
        if (!lemin->links->visited[final])
            break ;
        add_path(lemin, parent, final);
        adjacent_paths(lemin, lemin->paths[lemin->count - 1], start, final);
        i++;
    }
}
