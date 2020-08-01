#include "../includes/lemin.h"

static int is_duplicate(int src, t_path *dst)
{
    // printf("\e[93mis_duplicate\e[0m\n");
    int i;

    i = -1;
    while (++i < dst->len)
        if (dst->path[i] == src)
            return (1);
    return (0);
}

static void get_duplicate(t_shortpath *shortpath)
{
    // printf("\e[93mget_duplicate\e[0m\n");
    t_path *spurpaths[100];
    int i;
    int j;
    int k;

    i = -1;
    spurpaths[0] = shortpath->rootpath;
    while (shortpath->spurpaths[++i])
        spurpaths[i + 1] = shortpath->spurpaths[i];
    spurpaths[i + 1] = NULL;
    i = -1;
    while (spurpaths[++i])
    {
        j = -1;
        spurpaths[i]->dupl = 0;
        while (++j < spurpaths[i]->len)
        {
            k = -1;
            while (spurpaths[++k])
                if (spurpaths[k] != spurpaths[i])
                    if (is_duplicate(spurpaths[i]->path[j], spurpaths[k]))
                        spurpaths[i]->dupl += 1;
        }
    }
}

void duplicate_paths(t_shortpath **shortpaths)
{
    // printf("\e[92mduplicate_paths\e[0m\n");
    int i;

    i = -1;
    while (shortpaths[++i])
        get_duplicate(shortpaths[i]);
}