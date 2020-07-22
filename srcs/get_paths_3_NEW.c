#include "../includes/lemin.h"

static int  get_countpaths(t_node **paths)
{
    // printf("get_countpaths\n");
    int i;

    i = 0;
    while (paths[i])
        i++;
    return (i);
}

static void sortpaths(t_node **paths)
{
    // printf("sortpaths\n");
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

static int  cmp_paths(t_node *shortpath, t_node *spurpath)
{
    // printf("\e[94mcmp_paths\e[0m\n");
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
    // printf("shortpath = %d | j = %d\n", i, j);
    if (i == j)
        return (1);
    return (0);
}

static int  setlink(t_links *links, t_node *node, int set)
{
    // printf("setlink = %d\n", set);
    t_node  *tmp;

    if (node->next)
    {
        tmp = links->adjace[node->id];
        while (tmp)
        {
            if (tmp->id == node->next->id)
            {
                tmp->path = set;
                return (1);
            }
            tmp = tmp->next;
        }
    }
    return (0);
}

static void add_path(t_lemin *lemin, t_node **paths, int *parent)
{
    // printf("add_path\n");
    t_node      **rooms;
    t_node      *tmp;
    int         final;
    int         count;

    rooms = lemin->rooms->hroom;
    final = lemin->rooms->end->id;
    count = get_countpaths(paths);
    if (!lemin->links->visited[final])
    {
        // printf("\e[91mno path\e[0m\n");
        return ;
    }
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
    // printf("search_path\n");
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
            if (tmp->path == 0)
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

static t_node *get_shortspurpath(t_node **spurpaths, t_node *shortpath)
{
    // printf("get_shortspurpath\n");
    t_node  *tmp;
    int     i;

    i = 0;
    sortpaths(spurpaths);
    tmp = spurpaths[i];
    if (cmp_paths(shortpath, tmp))
        return (NULL);
    spurpaths[i] = NULL;
    while (spurpaths[i + 1])
    {
        spurpaths[i] = spurpaths[i + 1];
        spurpaths[i + 1] = NULL;
        i++;
    }
    return (tmp);
}

static void rebuildgraph(t_lemin *lemin, t_node *shortpath, int set)
{
    // printf("rebuildgraph\n");
    int final;

    final = lemin->rooms->end->id;
    while (shortpath)
    {
        setlink(lemin->links, shortpath, set);
        shortpath = shortpath->next;
    }
}

static void get_spurpaths(t_lemin *lemin, t_node *shortpath, int *parent)
{
    // printf("\e[92mget_spurpaths\e[0m\n");
    int     start;
    // int     final;
    // int     count;
    t_node  *tmp;

    // count = 0;
    start = lemin->rooms->start->id;
    tmp = shortpath;
    while (setlink(lemin->links, tmp, DEL))
    {
        search_path(lemin, creat_queue(), parent, start);
        add_path(lemin, lemin->spurpath, parent);
        setlink(lemin->links, tmp, SET);
        tmp = tmp->next;
    }
    ////////////////////
    // print_paths_2(lemin->spurpath);
    ////////////////////
    rebuildgraph(lemin, shortpath, DEL);
}

static void get_shortpaths(t_lemin *lemin, int *parent, int final)
{
    // printf("\e[92mget_shortpaths\e[0m\n");
    t_node  **shortpaths;
    t_node  *tmp;
    int     i;

    ////////////////////
    // print_paths_2(lemin->paths);
    ////////////////////
    i = lemin->count;
    shortpaths = lemin->paths;
    if (!lemin->links->visited[final])
        return ;
    get_spurpaths(lemin, shortpaths[i], parent);
    tmp = get_shortspurpath(lemin->spurpath, shortpaths[i]);
    if (tmp != NULL)
    {
        shortpaths[i + 1] = tmp;
        lemin->count++;
    }
    rebuildgraph(lemin, shortpaths[i + 1], SET);
    get_shortpaths(lemin, parent, final);

}

void        get_paths(t_lemin* lemin)
{
    // printf("\e[92mget_paths\e[0m\n");
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
    if (lemin->links->visited[final])
        get_shortpaths(lemin, parent, final);
}
