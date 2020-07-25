#include "../includes/lemin.h"

static int      get_count(t_path **paths)
{
    // printf("get_count\n");
    int i;

    i = 0;
    while (paths[i])
        i++;
    return (i);
}

static void     sort_spurpaths(t_path **paths)
{
    // printf("sortpaths\n");
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
    // printf("setlink = %s | %d-%d\n", set ? "OFF" : "ON", curr, next);
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

static void     search_path(t_lemin *lem, t_queue *queue, int *parent, int current)
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

static void     rebuildgraph(t_lemin *lemin, t_path *shortpath, int set)
{
    // printf("rebuildgraph\n");
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

static int      get_newshort(t_path **shortpaths, t_path **spurpaths, t_lemin *lem)
{
    // printf("get_newshort\n");
    int     i;
    int     j;
    int     k;
    int     *edge;

    i = 0;
    edge = NULL;
    j = get_count(spurpaths);
    k = get_count(shortpaths);
    sort_spurpaths(spurpaths);
    while (i < j)
    {
        if (!cmp_paths(shortpaths, spurpaths[i], &edge, lem))
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
    // printf("\e[92mget_newpath\e[0m\n");
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
    // printf("\e[92mget_spurpaths\e[0m\n");
    t_path  *new;
    int     *tmp;
    int     *edge;
    int     i;

    i = -1;
    edge = NULL;
    tmp = shortpath->path;
    while (tmp[++i + 1] != -1)
    {
        setlink(lemin->links, tmp[i], tmp[i + 1], DEL);
        search_path(lemin, creat_queue(), parent, lemin->start);
        if (lemin->links->visited[lemin->final])
        {
            if ((new = get_newpath(parent, lemin->final))->len < 128)
            {
                if (!cmp_paths(lemin->spurpaths, new, &edge, lemin))
                    lemin->spurpaths[get_count(lemin->spurpaths)] = new;
            }
            else
                return (0);
        }
        setlink(lemin->links, tmp[i], tmp[i + 1], SET);
    }
    return (1);
}

static void     get_shortpaths(t_lemin *lemin, int *parent)
{
    // printf("\e[92mget_shortpaths\e[0m\n");
    t_path  **shortpaths;
    t_path  **spurpaths;
    int     prim;
    int     i;

    shortpaths = lemin->shortpaths;
    spurpaths = lemin->spurpaths;
    i = 0;
    prim = 0;
    while (get_spurpaths(lemin, shortpaths[i], parent))
    {
        if (!prim++)
        {
            rebuildgraph(lemin, shortpaths[i], DEL);
            shortpaths[i] = NULL;
            if (get_newshort(shortpaths, spurpaths, lemin))
                rebuildgraph(lemin, shortpaths[i], SET);
        }
        if (!lemin->links->visited[lemin->final])
            break ;
        if (shortpaths[i])
            rebuildgraph(lemin, shortpaths[i], DEL);
        if (get_newshort(shortpaths, spurpaths, lemin))
            rebuildgraph(lemin, shortpaths[++i], SET);
    }
}

void        get_paths(t_lemin* lemin)
{
    // printf("\e[92mget_paths\e[0m\n");
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
    print_paths_2(lemin);
}


// static int      get_spurpaths(t_lemin *lemin, t_path *shortpath, int *parent)
// {
//     printf("\e[92mget_spurpaths\e[0m\n");
//     t_path  *new;
//     int     *tmp;
//     int     *edge;
//     int     i;

//     i = -1;
//     edge = NULL;
//     tmp = shortpath->path;
//     while (tmp[++i + 1] != -1)
//     {
//         setlink(lemin->links, tmp[i], tmp[i + 1], DEL);
//         search_path(lemin, creat_queue(), parent, lemin->start);
//         if (!lemin->links->visited[lemin->final])
//         {
//             setlink(lemin->links, tmp[i], tmp[i + 1], SET);
//             continue ;
//         }
//         if ((new = get_newpath(parent, lemin->final))->len < 256)
//         {
//             print_paths(new);
//             if (!cmp_paths(lemin->spurpaths, new, &edge, lemin))
//                 lemin->spurpaths[get_count(lemin->spurpaths)] = new;
//             else
//             {
//                 printf("\e[95medge = %d-%d\e[0m\n", *edge, *(edge + 1));
//                 setlink(lemin->links, *edge, *(edge + 1), DEL);
//                 --i;
//                 continue ;
//             }
//         }
//         else
//             return (0);
//         setlink(lemin->links, tmp[i], tmp[i + 1], SET);
//     }
//     return (1);
// }