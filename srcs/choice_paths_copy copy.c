#include "../includes/lemin.h"

// static int      paths_count(t_path **paths)
// {
//     int i;

//     i = 0;
//     while (paths[i])
//         i++;
//     return (i);
// }

static int      calc_step(t_path **paths, t_path *new, int ant)
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
        while (unique[i])
        {
            if (is_duplicate(unique[i], new))
                return (0);
            i++;
        }
    }
    return (1);
}

static t_path   *get_unique(t_shortpath **shortpaths, t_path **paths, t_path **unique)
{
    int i;
    int j;
    int k;

    i = 0;
    while (unique[i])
        i++;
    while (paths[j])
    {
        k = 0;
        while (shortpaths[k])
        {
            int 
        }
    }
}

static t_path **bestpaths(t_lemin *lemin, t_shortpath **shortpaths)
{
    t_path  **unique;
    t_path  *tmp[100];
    int     i;
    int     j;
    int     k;

    lemin->count = 0;
    k = 0;
    i = 0;
    unique = malloc(sizeof(t_path *) * 100);
    ft_memset(unique, 0, sizeof(t_path *) * 100);
    unique[k++] = shortpaths[0]->spurpaths[0];
    while (shortpaths[i])
    {
        j = 0;
        ft_memset(unique, 0, sizeof(t_path *) * 100);
        ft_memcpy(tmp, unique, sizeof(t_path *) * 100);
        if (get_unique(shortpaths[i + 1], shortpaths[i]->spurpaths, tmp))
            unique[k++] = get_unique(shortpaths[i], \
                                shortpaths[i]->spurpaths, tmp);
        i++;
    }
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
