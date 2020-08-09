#include "../includes/lemin.h"

static int      paths_count(t_path **paths)
{
    int i;

    i = 0;
    while (paths[i])
        i++;
    return (i);
}

static int      calculate_step(t_path **paths, int ant)
{
    printf("calculate_step\n");
    int i;
    int len;
    int step_new;
    int step_old;

    i = 0;
    len = 0;
    step_new = INT32_MAX;
    step_old = INT32_MAX;
    while (paths[i])
    {
        len += paths[i]->len;
        i++;
        step_new = (len / i) + (ant / i);
        if (step_new < step_old)
            step_old = step_new;
    }
    // printf("step_old %d | step_new %d\n", step_old, step_new);
    return (step_old);
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
        while (unique[i])
        {
            if (is_duplicate(unique[i], new))
                return (0);
            i++;
        }
    }
    return (1);
}

static t_path   *get_unique(t_lemin *lemin, t_shortpath **shortpaths, t_path **unique)
{
    printf("get_unique\n");
    t_path  *tmp[100];
    t_path  *path;
    int     step;
    int     count;
    int     i;
    int     j;
    int     k;

    k = -1;
    path = NULL;
    step = INT32_MAX;
    while (shortpaths[0]->spurpaths[++k])
    {
        if (is_unique(shortpaths[0]->spurpaths[k], unique))
        {
            ft_memset(tmp, 0, sizeof(t_path *) * 100);
            ft_memcpy(tmp, unique, sizeof(t_path *) * 100);
            count = paths_count(tmp);
            tmp[count++] = shortpaths[0]->spurpaths[k];
            i = 0;
            while (shortpaths[++i])
            {
                j = -1;
                while (shortpaths[i]->spurpaths[++j])
                    if (is_unique(shortpaths[i]->spurpaths[j], tmp))
                    {
                        tmp[count++] = shortpaths[i]->spurpaths[j];
                    }
            }
            if (step >= calculate_step(tmp, lemin->ants))
            {
                // printf("step_1\n");
                path = shortpaths[0]->spurpaths[k];
            }
        }
    }
    return (path);
}

static t_path **bestpaths(t_lemin *lemin, t_shortpath **shortpaths)
{
    t_path  **unique;
    t_path  *tmp;
    int     i;
    int     j;
    int     k;

    lemin->count = 0;
    k = 0;
    i = 1;
    unique = malloc(sizeof(t_path *) * 100);
    ft_memset(unique, 0, sizeof(t_path *) * 100);
    unique[k++] = shortpaths[0]->spurpaths[0];
    while (shortpaths[i])
    {
        // printf("step_1\n");
        if ((tmp = get_unique(lemin, shortpaths + i, unique)))
            unique[k++] = tmp;
        i++;
    }
    j = -1;
    while (unique[++j])
        print_paths(unique[j], lemin);
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
