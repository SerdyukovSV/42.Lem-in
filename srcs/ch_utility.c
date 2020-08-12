#include "../includes/lemin.h"

int  get_steps(t_path **paths, t_path *new, int ant)
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
    return ((len / count) + (ant / count));
}

int  is_duplicate(t_path *src, t_path *dst)
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

int  is_unique(t_path *new, t_path **unique)
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

int  is_replace(t_lemin *lemin, t_path *replace, t_path **tmp, t_path *new)
{
    int i;
    int s1;
    int s2;

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