#include "../includes/lemin.h"

// static int  get_steps2(t_path **paths, t_path *new, int ant)
// {
//     int i;
//     int len;
//     int s1;
//     int s2;

//     i = 0;
//     len = 0;
//     s1 = INT32_MAX;
//     s2 = INT32_MAX;
//     while (paths[i])
//     {
//         len += paths[i]->len;
//         i++;
//         s1 = (len / i) + (ant / i);
//         if (s1 < s2)
//             s2 = s1;
//     }
//     if (new)
//     {
//         len += new->len;
//         i++;
//         s1 = (len / i) + (ant / i);
//         if (s1 < s2)
//             s2 = s1;
//     }
//     // printf("count %d | len %d\t", count, len);
//     return (s2);
// }

static int get_steps(t_path **paths, t_path *new, int ant)
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
    // printf("count %d | len %d\t", count, len);
    return ((len / count) + (ant / count));
}

static int  is_duplicate(t_path *src, t_path *dst)
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

static int  is_unique(t_path *new, t_path **unique)
{
    int i;

    i = 0;
    if (new)
    {
        while (unique[i] || unique[i + 1])
        {
            if (unique[i])
                if (is_duplicate(unique[i], new))
                    return (0);
            i++;
        }
    }
    return (1);
}

static int  is_replace(t_lemin *lemin, t_path *replace, t_path **tmp, t_path *new)
{
    int i;
    int s1;
    int s2;
    // t_path *t1[100];
    // t_path *t2[100];

    i = 0;
    while (tmp[i])
        i++;
    if (!is_unique(new, tmp))
        return (0);
    if (!is_duplicate(replace, new))
    {
        if (is_unique(replace, tmp))
        {
            tmp[i] = replace;
            // ft_memcpy(t1, tmp, sizeof(t_path *) * 100);
            // ft_memcpy(t2, lemin->unique, sizeof(t_path *) * 100);
            // sort_unique(t1);
            // sort_unique(t2);
            s1 = get_steps(tmp, new, lemin->ants);
            s2 = get_steps(lemin->unique, NULL, lemin->ants);
            if (s1 >= s2)
                return (-1);
            lemin->unique[i] = replace;
            return (1);
        }
    }
    return (0);
}

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
        // paths++;
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
                continue ;
            j++;
        }
        i++;
    }
    sort_unique(lemin->unique);
    // printf("-------------unique-------------\n");
    // i = -1;
    // while (lemin->unique[++i])
    //     print_paths(lemin->unique[i], lemin);
    // // printf("step = %d\n", get_steps(lemin->unique, NULL, lemin->ants));
    // printf("step = %d\n", get_steps2(lemin->unique, NULL, lemin->ants));
}
