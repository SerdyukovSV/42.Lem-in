#include "../includes/lemin.h"

// static int      paths_count(t_path **paths)
// {
//     int i;

//     i = 0;
//     while (paths[i])
//         i++;
//     return (i);
// }

static int calc_step(t_path **paths, t_path *new, int ant)
{
    int i;
    int len;
    int count;

    i = 0;
    len = 0;
    count = 0;
    if (new)
    {
        len = new->len;
        count = 1;
    }
    while (paths[i] || paths[i + 1])
    {
        if (paths[i])
        {
            len += paths[i]->len;
            count++;
        }
        i++;
    }
    printf("count %d | len %d\t", count, len);
    return ((len / count) + (ant / count));
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

static int      is_unique(t_path *new, t_path **unique)
{
    // printf("is_unique\n");
    int i;

    i = 0;
    if (new)
    {
        // printf("step_1\n");
        while (unique[i] || unique[i + 1])
        {
            // printf("step_2\n");
            if (unique[i])
            {
                // printf("step_3\n");
                if (is_duplicate(unique[i], new))
                {
                    // printf("return (0)\n");
                    return (0);
                }
            }
            i++;
        }
    }
    return (1);
}

static t_path   **replacepath(t_shortpath **shortpaths, t_path **unique, t_path *new, t_lemin *lemin)
{
    printf("replacepath\n");
    t_path  **paths;
    t_path  *tmp[100];
    int     i;

    ft_memset(tmp, 0, sizeof(t_path *) * 100);
    ft_memcpy(tmp, unique, sizeof(t_path *) * 100);
    i = 0;
    while (!is_duplicate(tmp[i], new))
        i++;
    if (tmp[i])
        print_paths(tmp[i], lemin);
    int j = 0;
    while (shortpaths[j]->spurpaths[0]->path[0] != tmp[i]->path[0])
        j++;
    paths = shortpaths[j]->spurpaths;
    while (*paths != tmp[i])
        paths++;
    tmp[i] = NULL;
    printf("i = %d\n", i);
    while (*paths)
    {
        printf("paths[%d]\n", (*paths)->len);
        if (!is_duplicate(*paths, new))
        {
            printf("step_1\n");
            if (is_unique(*paths, tmp))
            {
                printf("step_2\n");
                tmp[i] = *paths;
                if (!is_unique(new, tmp))
                    return (replacepath(shortpaths, tmp, new, lemin));
                printf("calc: %d > %d\n", calc_step(tmp, new, lemin->ants), calc_step(unique, NULL, lemin->ants));
                if (calc_step(tmp, new, lemin->ants) >= calc_step(unique, NULL, lemin->ants))
                    return (NULL);
                ft_memcpy(unique, tmp, sizeof(t_path *) * 100);
                return (unique);
            }
        }
        paths++;
    }
    return (NULL);
}

static t_path **bestpaths(t_lemin *lemin, t_shortpath **shortpaths)
{
    t_path  **unique;
    t_path  **tmp;
    int     i;
    int     j;
    int     k;

    lemin->count = 0;
    k = 0;
    i = 0;
    unique = malloc(sizeof(t_path *) * 100);
    ft_memset(unique, 0, sizeof(t_path *) * 100);
    while (shortpaths[i])
    {
        j = 0;
        printf("shortpaths[%d]\n", i);
        while (shortpaths[i]->spurpaths[j])
        {
            printf("spurpaths[%d]\n", shortpaths[i]->spurpaths[j]->len);
            if (is_unique(shortpaths[i]->spurpaths[j], unique))
            {
                printf("add unique\n");
                // print_paths(shortpaths[i]->spurpaths[j], lemin);
                unique[k++] = shortpaths[i]->spurpaths[j];
                int l = -1;
                while (unique[++l])
                    print_paths(unique[l], lemin);
                break ;
            }
            else if ((tmp = replacepath(shortpaths, unique, shortpaths[i]->spurpaths[j], lemin)))
            {
                printf("new unique\n");
                unique = tmp;
                continue ;
            }
            j++;
        }
        i++;
    }
    printf("-------------unique-------------\n");
    i = -1;
    while (unique[++i])
        print_paths(unique[i], lemin);
    printf("step = %d\n", calc_step(unique, NULL, lemin->ants));
    return (unique);
}

t_shortpath *choice_paths(t_lemin *lemin)
{
    // t_path  *paths[2000];
    // int     i;
    // int     j;
    // int     k;

    // k = 0;
    // i = -1;
    // while (lemin->shortpaths[++i])
    // {
    //     j = -1;
    //     while (lemin->shortpaths[i]->spurpaths[++j])
    //         paths[k++] = lemin->shortpaths[i]->spurpaths[j];
    // }
    // paths[k] = NULL;
    bestpaths(lemin, lemin->shortpaths);
    return (NULL);
}
