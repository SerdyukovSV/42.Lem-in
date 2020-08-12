#include "../includes/lemin.h"

void     possible_paths(t_lemin *lemin, t_path *rootpath)
{
    t_node  *tmp;
    int     i;

    i = -1;
    lemin->possible = 0;
    while (++i < rootpath->len)
    {
        tmp = lemin->links->adjace[rootpath->path[i]];
        while (tmp)
        {
            lemin->possible++;
            tmp = tmp->next;
        }
    }
}

void     setlink_spur(t_lemin *lemin, t_path *spurpaths, int root, int set)
{
    t_node  *tmp;
    int     i;

    i = 0;
    tmp = lemin->links->adjace[root];
    while (i < spurpaths->len - 1)
    {
        if (spurpaths->path[i++] == root)
        {
            while (tmp && tmp->id != spurpaths->path[i])
                tmp = tmp->next;
            if (tmp && tmp->id == spurpaths->path[i])
                tmp->path = set;
            break ;
        }
    }
}

void     setlink_root(t_lemin *lemin, int *rootpath, int set)
{
    t_node  *tmp;

    tmp = lemin->links->adjace[rootpath[0]];
    while (tmp && tmp->id != rootpath[1])
        tmp = tmp->next;
    if (tmp && tmp->id == rootpath[1])
    {
        tmp->path = set;
    }
}

void     setvertex(t_lemin *lemin, int vertex, int set)
{
    t_node  *src;
    t_node  *adj;
    int i;

    i = -1;
    src = lemin->links->adjace[vertex];
    while (src)
    {
        adj = lemin->links->adjace[src->id];
        while (adj)
        {
            if (adj->id == vertex)
            {
                adj->path = set;
                break ;
            }
            adj = adj->next;
        }
        src = src->next;
    }
}

void     rebuildgraph(t_lemin *lemin, t_shortpath *shortpath, int set)
{
    t_path  *rootpath;
    t_path  **spurpaths;
    int     i;
    int     j;

    i = 0;
    rootpath = shortpath->rootpath;
    spurpaths = shortpath->spurpaths;
    while (i < rootpath->len && rootpath->path[i + 1] != -1)
    {
        setlink_root(lemin, &rootpath->path[i], set);
        j = -1;
        while (spurpaths[++j])
            setlink_spur(lemin, spurpaths[j], rootpath->path[i], set);
        setvertex(lemin, rootpath->path[i], set);
        i++;
    }
}