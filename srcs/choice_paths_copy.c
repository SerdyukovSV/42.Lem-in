#include "../includes/lemin.h"

static int      paths_count(t_path **paths)
{
    int i;

    i = 0;
    while (paths[i])
        i++;
    return (i);
}

static t_path   **new_unique(t_path **p1, t_path **p2)
{
    printf("new_unique\n");
    int i;

    i = 0;
    if (paths_count(p1) > paths_count(p2))
    {
        printf("p1 > p2\n");
        while (p1[i])
        {
            if (p1[i] != p2[i])
                p2[i] = p1[i];
            i++;
        }
    }
    return (p2);
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

t_path          **uniquepaths(t_path **paths, t_path **unique, int pos, t_lemin *lemin)
{
    printf("uniquepaths\n");
    t_path  *tmp[100];
    int     i;
    int     k;

    print_paths(*paths, lemin);
    // printf("\n");
    while (*paths != unique[pos])
    {
        system("sleep 1");
        i = 0;
        k = pos - 1;
        ft_memset(tmp, 0, sizeof(t_path *) * 100);
        ft_memcpy(tmp, unique, sizeof(t_path *) * (pos - 1));
        printf("tmp = \n");
        print_paths(*tmp, lemin);
        printf("\n");
        while (paths[i])
        {
            if (is_unique(paths[i], tmp))
                tmp[k++] = paths[i];
            i++;
        }
        i = -1;
        while (tmp[++i])
            print_paths(tmp[i], lemin);
        unique = new_unique(tmp, unique);
        paths++;
    }
    if (*paths)
        return (uniquepaths(paths, unique, pos + 1, lemin));
    return (unique);
}

static t_path **bestpaths(t_lemin *lemin, t_path **paths)
{
    t_path  **unique;
    int     i;
    int     k;

    k = lemin->ants;
    k = 0;
    i = -1;
    unique = malloc(sizeof(t_path *) * 100);
    ft_memset(unique, 0, sizeof(t_path *) * 100);
    while (paths[++i])
        if (is_unique(paths[i], unique))
            unique[k++] = paths[i];
    unique[k] = NULL;
    unique = uniquepaths(paths, unique, 1, lemin);
    i = -1;
    while (unique[++i])
        print_paths(unique[i], lemin);
    return (NULL);
}

t_shortpath *choice_paths(t_lemin *lemin)
{
    t_path  *paths[2000];
    int     i;
    int     j;
    int     k;

    k = 0;
    i = -1;
    while (lemin->shortpaths[++i])
    {
        j = -1;
        while (lemin->shortpaths[i]->spurpaths[++j])
            paths[k++] = lemin->shortpaths[i]->spurpaths[j];
    }
    paths[k] = NULL;
    bestpaths(lemin, paths);
    return (NULL);
}


// t_path   **uniquepaths(t_path **paths, t_path **unique, int pos)
// {
//     t_path  *tmp[100];
//     int     i;
//     int     j;
//     int     k;

//     i = -1;
//     while (paths[++i])
//     {
//         k = 0;
//         j = -1;
//         ft_memset(tmp[i], 0, sizeof(t_path *) * 100);
//         tmp[k++] = paths[i];
//         while (paths[++j])
//         {
//             if (is_unique(paths[j], tmp))
//                 tmp[k++] = paths[j];
//         }
//     }
//     return (unique);
// }