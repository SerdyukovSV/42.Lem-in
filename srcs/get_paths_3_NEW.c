#include "../includes/lemin.h"

static int  get_count(t_path **paths)
{
    printf("get_countpaths\n");
    int i;

    i = 0;
    while (paths[i])
        i++;
    return (i);
}

static void sort_spurpaths(t_path **paths)
{
    printf("sortpaths\n");
    t_path  *tmp;
    int     i;
    int     j;

    i = -1;
    while (paths[++i])
    {
        j = -1;
        while (paths[++j])
        {
            if (paths[j + 1] && paths[j]->len > paths[j + 1]->len)
            {
                tmp = paths[j];
                paths[j] = paths[j + 1];
                paths[j + 1] = tmp;
            }
        }
    }
}

static int      setlink(t_links *links, int curr, int next, int set)
{
    printf("setlink = %d\n", set);
    t_node  *tmp;

    tmp = links->adjace[curr];
    while (tmp)
    {
        if (tmp->id == next)
        {
            tmp->path = set;
            return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

// static void     add_path(t_lemin *lemin, t_node **paths, int *parent)
// {
//     // printf("add_path\n");
//     t_node      **rooms;
//     t_node      *tmp;
//     int         final;
//     int         count;

//     rooms = lemin->rooms->hroom;
//     final = lemin->rooms->end->id;
//     count = get_countpaths(paths);
//     if (!lemin->links->visited[final])
//     {
//         printf("\e[91mno path\e[0m\n");
//         return ;
//     }
//     paths[count] = room_dup(rooms[final]);
//     while (parent[final] != -1)
//     {
//         tmp = room_dup(rooms[parent[final]]);
//         tmp->next = paths[count];
//         paths[count] = tmp;
//         final = parent[final];
//     }
// }

static void     search_path(t_lemin *lem, t_queue *queue, int *parent, int current)
{
    printf("search_path\n");
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

static void     rebuildgraph(t_lemin *lemin, t_path *shortpath, int set)
{
    printf("rebuildgraph\n");
    int *tmp;
    int i;

    i = 0;
    tmp = shortpath->path;
    while (tmp[i + 1] != -1)
    {
        setlink(lemin->links, tmp[i], tmp[i + 1], set);
        i++;
    }
}

static int      get_newshort(t_path **shortpaths, t_path **spurpaths)
{
    printf("get_newshort\n");
    int     i;
    int     j;
    int     k;

    i = 0;
    j = get_count(spurpaths);
    k = get_count(shortpaths);
    sort_spurpaths(spurpaths);
    while (i < j)
    {
        if (!cmp_paths(shortpaths, spurpaths[i]))
        {
            shortpaths[k] = spurpaths[i];
            return (1);
        }
        i++;
    }
    return (0);
}

static t_path   *get_newpath(int *parent, int fin)
{
    printf("\e[92mget_newpath\e[0m\n");
    t_path  *newpath;
    int     tmp[256];
    int     i;

    if (!(newpath = malloc(sizeof(t_path))))
        return (NULL);
    i = 0;
    ft_memset(tmp, -1, sizeof(int) * 256);
    ft_memset(newpath->path, -1, sizeof(int) * 256);
    tmp[i] = fin;
    while (parent[fin] != -1)
    {
        fin= parent[fin];
        tmp[++i] = fin;
    }
    newpath->len = -1;
    while (++newpath->len <= i)
        newpath->path[newpath->len] = tmp[i - newpath->len];
    return (newpath);
}

static int      get_spurpaths(t_lemin *lemin, t_path *shortpath, int *parent)
{
    printf("\e[92mget_spurpaths\e[0m\n");
    t_path  *new;
    int     *tmp;
    int     i;

    i = 0;
    tmp = shortpath->path;
    while (tmp[i + 1] != -1)
    {
        setlink(lemin->links, tmp[i], tmp[i + 1], DEL);
        search_path(lemin, creat_queue(), parent, lemin->start);
        if (!lemin->links->visited[lemin->final])
            continue ;
        if ((new = get_newpath(parent, lemin->final))->len >= 128)
            return (0);
        else if (cmp_paths(lemin->spurpaths, new))
            lemin->spurpaths[get_count(lemin->spurpaths)] = new;
        setlink(lemin->links, tmp[i], tmp[i + 1], SET);
        i++;
    }
    return (1);
}

static void     get_shortpaths(t_lemin *lemin, int *parent)
{
    printf("\e[92mget_shortpaths\e[0m\n");
    t_path  **shortpaths;
    t_path  **spurpaths;
    int     i;
    int     prime;

    prime = 0;
    shortpaths = lemin->shortpaths;
    spurpaths = lemin->spurpaths;
    // i = get_count(shortpaths);
    i = 0;
    while (get_spurpaths(lemin, shortpaths[i], parent))
    {
        if (!prime)
        {
            rebuildgraph(lemin, shortpaths[i], DEL);
            shortpaths[i] = NULL;
            prime++;
        }
        if (!lemin->links->visited[lemin->final])
            break ;
        if (shortpaths[i])
            rebuildgraph(lemin, shortpaths[i], DEL);
        if (get_newshort(shortpaths, spurpaths))
        {
            rebuildgraph(lemin, shortpaths[++i], SET);
        }
    }
}

void        get_paths(t_lemin* lemin)
{
    printf("\e[92mget_paths\e[0m\n");
    int parent[lemin->rooms->total];

    lemin->primpath = NULL;
    lemin->spurpaths = malloc(sizeof(t_path *) * 500);
    lemin->shortpaths = malloc(sizeof(t_path *) * 100);
    if (!lemin->shortpaths || !lemin->spurpaths)
        ft_error(ERR);
    search_path(lemin, creat_queue(), parent, lemin->start);
    if (lemin->links->visited[lemin->final])
    {
        lemin->primpath = get_newpath(parent, lemin->final);
        lemin->shortpaths[0] = lemin->primpath;
        get_shortpaths(lemin, parent);
    }
    printf("\e[92mSUCCES\e[0m\n");
}
