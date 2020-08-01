#include "../includes/lemin.h"

int  cmp_paths(t_path **spurpaths, t_path *newpath, t_lemin *lemin)
{
    // printf("\e[92mcmp_paths\e[0m\n");
    int     i;
    int     j;
    int     equal;

    int g;
    g = lemin->count;
    while (*spurpaths)
    {
        i = -1;
        equal = 0;
        while (++i < (*spurpaths)->len)
        {
            j = -1;
            while (++j < newpath->len)
                if (newpath->path[j] == (*spurpaths)->path[i])
                    equal++;
        }
        if (equal == (*spurpaths)->len)
            return (1);
        spurpaths++;
    }
    return (0);
}

