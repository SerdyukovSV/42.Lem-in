#include "../includes/lemin.h"

static void sort_paths(t_path **paths)
{
    t_path  *tmp;
    int     i;
    int     j;

    i = -1;
    while (paths[++i])
    {
        j = -1;
        while (paths[++j])
        {
            if (paths[j + 1] && paths[j]->dupl > paths[j + 1]->dupl)
            {
                tmp = paths[j];
                paths[j] = paths[j + 1];
                paths[j + 1] = tmp;
            }
        }
    }
}

static int  is_duplicate(int src, t_path *dst)
{
    // printf("\e[93mis_duplicate\e[0m : ");
    // printf(" %s\n", rooms->hroom[dst->path[0]]->name);
    int i;

    i = -1;
    while (++i < dst->len)
        if (dst->path[i] == src)
            return (1);
    return (0);
}

static int  get_duplicate(t_path *src, t_path **all, int len)
{
    // printf("\e[91mget_duplicate\e[0m\n");
    // int tmp[100];
    int dup;
    int i;
    int j;

    i = -1;
    dup = 0;
    while (++i < src->len - 1)
    {
        j = -1;
        while (++j < len)
        {
            if (all[j] && all[j] != src/*  && !tmp[j] */)
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
        allpaths[j]->dupl = get_duplicate(allpaths[j], allpaths, i + 1);
    }
    sort_paths(allpaths);
}

t_shortpath *choice_paths(t_lemin *lemin)
{
    // t_shortpath *shortpaths;
    int         i;

    i = 0;
    // shortpaths = malloc(sizeof(t_shortpath));
    // shortpaths->rootpath = lemin->shortpaths[i]->rootpath;
    // shortpaths->spurpaths = malloc(sizeof(t_path *) * 100);
    // while (lemin->shortpaths[++i])
    //     shortpaths->spurpaths[i - 1] = lemin->shortpaths[i]->rootpath;
    // shortpaths->spurpaths[i - 1] = NULL;
    i = -1;
    while (lemin->shortpaths[++i])
        duplicate_paths(lemin->shortpaths[i]);

    return (NULL);
}