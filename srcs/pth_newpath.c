#include "../includes/lemin.h"

t_path   *newpath(int *parent, int fin)
{
    t_path  *newpath;
    int     tmp[256];
    int     i;

    if (!(newpath = malloc(sizeof(t_path))))
        return (NULL);
    i = 0;
    newpath->flow = -1;
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

t_path   *pathjoin(t_path *rootpath, t_path *newpath, int cur)
{
    t_path  *tmp;
    int     i;
    int     j;

    tmp = malloc(sizeof(t_path));
    ft_memset(tmp->path, -1, sizeof(int) * 256);
    tmp->len = 0;
    tmp->flow = -1;
    if (newpath)
    {
        i = -1;
        while (rootpath->path[++i] != cur)
            tmp->path[i] = rootpath->path[i];
        j = 0;
        while (j < newpath->len)
            tmp->path[i++] = newpath->path[j++];
        tmp->len = i;
        free(newpath);
    }
    return (tmp);
}