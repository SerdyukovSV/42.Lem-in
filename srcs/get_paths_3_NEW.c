#include "../includes/lemin.h"

static int  get_countpaths(t_node **paths)
{
    int i;

    i = 0;
    while (paths[i])
        i++;
    return (i);
}

static void sortpaths(t_node **paths)
{
    t_node  *tmp;
    int     i;
    int     j;

    i = -1;
    while (paths[++i])
    {
        j = -1;
        while (paths[++j])
        {
            if (paths[j + 1] && path_len(paths[j]) > path_len(paths[j + 1]))
            {
                tmp = paths[j];
                paths[j] = paths[j + 1];
                paths[j + 1] = tmp;
            }
        }
    }
}

static int  cmp_paths(t_node *shortpath, t_node *spurpath, int fin)
{
    t_node  *tmp;
    int     i;
    int     j;

    j = 0;
    i = path_len(shortpath);
    while (shortpath)
    {
        tmp = spurpath;
        while (tmp)
        {
            if (shortpath->id == tmp->id)
            {
                j++;
                break ;
            }
            tmp = tmp->next;
        }
        shortpath = shortpath->next;
    }
    if (i == j)
        return (1);
    return (0);
}

static int  set_link(t_links *links, t_node *node, int final, int set)
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

static void add_path(t_lemin *lemin, t_node **paths, int *parent)
{
    t_node      **rooms;
    t_node      *tmp;
    int         final;
    int         count;

    rooms = lemin->rooms->hroom;
    final = lemin->rooms->end->id;
    count = get_countpaths(paths);
    if (!lemin->links->visited[final])
        return ;
    paths[count] = room_dup(rooms[final]);
    while (parent[final] != -1)
    {
        tmp = room_dup(rooms[parent[final]]);
        tmp->next = paths[count];
        paths[count] = tmp;
        final = parent[final];
    }
}

static void search_path(t_lemin *lem, t_queue *queue, int *parent, int current)
{
    t_node      *tmp;

    ft_bzero(lem->links->visited, sizeof(int) * lem->rooms->total);
    ft_bzero(parent, sizeof(int) * lem->rooms->total);
    enqueue(queue, current);
    parent[current] = -1;
    while(queue->rear != -1)
    {
        current = dequeue(queue);
        lem->links->visited[current] = 1;
        tmp = lem->links->adjace[current];
        while(tmp)
        {
            if (tmp->path == 0 && tmp->id != lem->rooms->start->id)
            {
                if(lem->links->visited[tmp->id] == 0)
                {
                    enqueue(queue, tmp->id);
                    lem->links->visited[tmp->id] = 1;
                    parent[tmp->id] = current;
                }
            }
            tmp = tmp->next;
        }
    }
}

static void get_spurpaths(t_lemin *lemin, t_node *shortpath, int *parent)
{
    int     start;
    int     final;
    int     count;
    t_node  *tmp;

    count = 0;
    tmp = shortpath->next;
    shortpath = shortpath->next;
    while (set_link(lemin->links, shortpath, final, DEL))
    {
        search_path(lemin, creat_queue(), parent, start);
        add_path(lemin, lemin->spurpath, parent);
        set_link(lemin->links, shortpath, final, SET);
        shortpath = shortpath->next;
    }
    
}

static void get_shortpaths(t_lemin *lemin, int *parent, int final)
{
    t_node  *tmp;

    if (!lemin->links->visited[final])
        return ;
    get_spurpaths(lemin, parent, parent);
    sortpaths(lemin->spurpath);
    




    // while (tmp)
    // {
    //     del_set_link(lemin->links, tmp, final, 1);
    //     tmp = tmp->next;
    // }
}

void        get_paths(t_lemin* lemin)
{
    int parent[lemin->rooms->total];
    int start;
    int final;
    int i;

    i = 0;
    start = lemin->rooms->start->id;
    final = lemin->rooms->end->id;
    lemin->paths = creat_paths(lemin->rooms->total);
    lemin->spurpath = creat_paths(lemin->rooms->total);
    search_path(lemin, creat_queue(), parent, start);
    add_path(lemin, lemin->paths, parent);
    lemin->count++;
    if (lemin->links->visited[final])
        get_shortpaths(lemin, parent, final);
}
