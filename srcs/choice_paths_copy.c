#include "../includes/lemin.h"

static int      countpaths(t_path **paths)
{
    int i;

    i = 0;
    while (paths[i])
        i++;
    return (i);
}

static int      is_duplicate(t_path *src, t_path *dst)
{
    int i;
    int j;

    if (dst)
    {
        i = -1;
        while (++i < src->len - 1)
        {
            j = -1;
            while (++j < dst->len - 1)
                if (dst->path[j] == src->path[i])
                    return (1);
        }
    }
    return (0);
}

static int      is_unique(t_path *spur, t_path **paths)
{
    int i;

    i = 0;
    if (spur)
    {
        while (paths[i])
        {
            if (is_duplicate(paths[i], spur))
                return (0);
            i++;
        }
    }
    return (1);
}

static t_path   **get_uniquepaths(t_path **paths, t_path **unique, t_lemin *lemin)
{
    t_path  *tmp[100];
    int     i;
    int     j;
    int     k;
    int len;

    i = -1;
    while (paths[++i])
    {
        system("sleep 0.5");
        j = -1;
        k = 0;
        len = 0;
        ft_memset(tmp, 0, sizeof(t_path *) * 100);
        tmp[k] = paths[i];
        len += tmp[k]->len;
        print_paths(tmp[k], lemin);
        k++;
        while (paths[++j])
        {
            // system("sleep 0.05");
            if (is_unique(paths[j], tmp))
            {
                tmp[k] = paths[j];
                len += tmp[k]->len;
                print_paths(tmp[k], lemin);
                k++;
            }
        }
        printf("\e[93mcount = %d | ant = %d | len = %d | step = %d\e[0m\n", countpaths(tmp), lemin->ants, len, ((len / countpaths(tmp)) + (lemin->ants / countpaths(tmp))));
        if (countpaths(tmp) > countpaths(unique))
        {
            printf("tmp = new\n");
            unique = tmp;
        }
    }
    return (unique);
}

static t_path **bestpaths(t_lemin *lemin, t_shortpath **shortpaths)
{
    t_path  **unique;
    t_path  *paths[1000];
    int     i;
    int     j;
    int     k;

    k = 0;
    i = -1;
    unique = malloc(sizeof(t_path *) * 100);
    ft_memset(unique, 0, sizeof(t_path *) * 100);
    while (shortpaths[++i])
    {
        j = -1;
        while (shortpaths[i]->spurpaths[++j])
            paths[k++] = shortpaths[i]->spurpaths[j];
    }
    paths[k] = NULL;
    unique = get_uniquepaths(paths, unique, lemin);
    i = lemin->ants;
    // i = -1;
    // while (unique[++i])
    //     print_paths(unique[i], lemin);
    return (NULL);
}

t_shortpath *choice_paths(t_lemin *lemin)
{
    t_path **paths;
    // int         i;
    int         len;

    len = 0;
    // paths = malloc(sizeof(t_path *) * 100);
    paths = bestpaths(lemin, lemin->shortpaths);
    // i = -1;
    // while (paths[++i])
    //     len += paths[i]->len;
    // printf("count = %d | len = %d | step = %d\n", i, len, ((len / i) + (lemin->ants / i) - 1));
    // printf("------------unique_paths-----------\n");
    // i = -1;
    // while (paths[++i])
    //     print_paths(paths[i], lemin);
    return (NULL);
}
