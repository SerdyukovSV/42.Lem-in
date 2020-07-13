#include "../includes/lemin.h"

static void path_del(t_node *path)
{
    t_node *tmp;

    while (path)
    {
        tmp = path;
        path = path->next;
        free(tmp);
    }
}

static int cmp_paths(t_node *shortpath, t_node *paths, int fin)
{
    t_node *tmp;

    while (shortpath)
    {
        tmp = paths->next;
        while (tmp->next && shortpath->id != tmp->id)
            tmp = tmp->next;
        if (tmp->id == fin)
            shortpath = shortpath->next;
        else
            break ;
    }
    if (!shortpath)
        return (1);
    return (0);
}

t_node **new_paths(t_lemin *lemin, t_node **paths, int start)
{
    t_node  **new_p;
    int     duplicate;
    int     i;
    int     k;

    i = 0;
    k = 0;
    duplicate = 0;
    new_p = creat_paths(lemin->size);
    while (k <= start)
        new_p[k++] = paths[i++];
    while (paths[i])
    {
        if (cmp_paths(paths[start]->next, paths[i], lemin->rooms->end->id))
            new_p[k++] = paths[i];
        else if (++duplicate)
            path_del(paths[i]);
        i++;
    }
    if (duplicate)
        return (new_paths(lemin, new_p, start + 1));
    return (new_p);
}