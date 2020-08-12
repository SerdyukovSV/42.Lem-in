#include "../includes/lemin.h"

static int  replacepath(t_lemin *lemin, t_shortpath **shortpaths, t_path *new)
{
    t_path  **paths;
    t_path  *tmp[100];
    int     j;
    int     i;

    ft_memset(tmp, 0, sizeof(t_path *) * 100);
    ft_memcpy(tmp, lemin->unique, sizeof(t_path *) * 100);
    i = 0;
    while (!is_duplicate(tmp[i], new))
        i++;
    j = 0;
    while (shortpaths[j]->spurpaths[0]->path[0] != tmp[i]->path[0])
        j++;
    paths = shortpaths[j]->spurpaths;
    while (*paths != tmp[i])
        paths++;
    tmp[i] = NULL;
    while (*(++paths))
    {
        if ((i = is_replace(lemin, *paths, tmp, new)) == 1)
            return (1);
        else if (i == -1)
            return (0);
    }
    return (0);
}

void        choice_paths(t_lemin *lemin)
{
    t_shortpath **paths;
    int         i;
    int         j;
    int         k;

    i = 0;
    k = 0;
    paths = lemin->shortpaths;
    while (paths[i])
    {
        j = 0;
        while (paths[i]->spurpaths[j])
        {
            if (is_unique(paths[i]->spurpaths[j], lemin->unique))
            {
                lemin->unique[k++] = paths[i]->spurpaths[j];
                break ;
            }
            else if (replacepath(lemin, paths, paths[i]->spurpaths[j]))
                lemin->unique[k++] = paths[i]->spurpaths[j];
            j++;
        }
        i++;
    }
    sort_unique(lemin->unique);
}
