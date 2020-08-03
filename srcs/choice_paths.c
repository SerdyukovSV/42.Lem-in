#include "../includes/lemin.h"

// static void sort_paths(t_path **paths)
// {
//     t_path  *tmp;
//     int     i;
//     int     j;

//     i = -1;
//     while (paths[++i])
//     {
//         j = -1;
//         while (paths[++j])
//         {
//             if (paths[j + 1] && paths[j]->dupl > paths[j + 1]->dupl)
//             {
//                 tmp = paths[j];
//                 paths[j] = paths[j + 1];
//                 paths[j + 1] = tmp;
//             }
//         }
//     }
// }

static void replaceroot(t_shortpath **shortpath)
{
    t_path  *tmp;
    int     i;

    i = -1;
    while ((*shortpath)->spurpaths[++i])
    {
        if ((*shortpath)->rootpath->dupl > (*shortpath)->spurpaths[i]->dupl)
        {
            tmp = (*shortpath)->rootpath;
            (*shortpath)->rootpath = (*shortpath)->spurpaths[i];
            (*shortpath)->spurpaths[i] = tmp;
        }
    }
}

static int  is_duplicate(int src, t_path *dst)
{
    // printf("\e[93mis_duplicate\e[0m : ");
    int i;

    i = -1;
    if (dst)
    {
        while (++i < dst->len)
            if (dst->path[i] == src)
                return (1);
    }
    return (0);
}

static int  get_duplicate(t_path *src, t_path **all)
{
    // printf("\e[91mget_duplicate\e[0m\n");
    int dup;
    int i;
    int j;

    i = -1;
    dup = 0;
    while (++i < src->len - 1)
    {
        j = -1;
        while (all[++j])
        {
            if (all[j] != src)
                if (is_duplicate(src->path[i], all[j]))
                    dup++;
        }
    }
    return (dup);
}

static void duplicate_paths(t_shortpath *shortpath)
{
    // printf("\e[92mduplicate_paths\e[0m\n");
    t_path *allpaths[100];
    int i;
    int j;

    i = -1;
    allpaths[0] = shortpath->rootpath;
    while (shortpath->spurpaths[++i])
        allpaths[i + 1] = shortpath->spurpaths[i];
    allpaths[i + 1] = NULL;
    j = -1;
    while (allpaths[++j])
    {
        allpaths[j]->dupl = get_duplicate(allpaths[j], allpaths);
    }
}

static void get_uniquepaths(t_path **paths)
{
    // printf("\e[93mget_uniquepaths\e[0m\n");
    int     i;
    int     j;
    int     k;

    i = -1;
    while (paths[++i])
    {
        j = -1;
        while (++j < paths[i]->len - 1)
        {
            k = i;
            while (paths[++k])
            {
                if (is_duplicate(paths[i]->path[j], paths[k]))
                {
                    paths[k] = NULL;
                    while (paths[k + 1])
                    {
                        paths[k] = paths[k + 1];
                        paths[++k] = NULL;
                    }
                    k = i;
                }
            }
        }
    }
}

static t_path **remaining_paths(t_lemin *lemin, t_path **paths)
{
    int i;
    int j;
    int len;

    len = 0;
    while (paths[len])
        len++;
    i = 0;
    while (lemin->shortpaths[i])
    {
        j = -1;
        while (lemin->shortpaths[i]->spurpaths[++j])
            if (!get_duplicate(lemin->shortpaths[i]->spurpaths[j], paths))
                paths[len++] = lemin->shortpaths[i]->spurpaths[j];
        i++;
    }
    return (paths);
}

t_shortpath *choice_paths(t_lemin *lemin)
{
    t_path **paths;
    int         i;
    int         j;

    paths = malloc(sizeof(t_path *) * 100);
    i = -1;
    while (lemin->shortpaths[++i])
    {
        duplicate_paths(lemin->shortpaths[i]);
        replaceroot(&lemin->shortpaths[i]);
    }
    sort_rootpaths(lemin->shortpaths);
    i = -1;
    while (lemin->shortpaths[++i])
        paths[i] = lemin->shortpaths[i]->rootpath;
    paths[i] = NULL;
    get_uniquepaths(paths);
    j = -1;
    while (paths[++j])
        paths[j]->dupl = get_duplicate(paths[j], paths);
    j = -1;
    printf("-----------------------------\n");
    while (paths[++j])
        print_paths(paths[j], lemin);
    paths = remaining_paths(lemin, paths);
    j = -1;
    printf("------------remaining_paths-----------\n");
    while (paths[++j])
        print_paths(paths[j], lemin);
    return (NULL);
}
