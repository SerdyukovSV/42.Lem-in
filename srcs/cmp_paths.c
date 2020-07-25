#include "../includes/lemin.h"

int  cmp_paths(t_path **spurpaths, t_path *newpath, int **link, t_lemin *lem)
{
    // printf("\e[92mcmp_paths\e[0m\n");
    int     i;
    int     j;
    int     equal;

    int k;
    k = lem->count;
    while (*spurpaths)
    {
        i = -1;
        equal = 0;
        while (++i < (*spurpaths)->len)
        {
            j = -1;
            while (++j < newpath->len)
                if (newpath->path[j] == (*spurpaths)->path[i] /* && newpath->path[j] != lem->final && newpath->path[j] != lem->start */)
                {
                    *link = &newpath->path[j - 1];
                    equal++;
                    // return (1);
                }
        }
        if (equal == (*spurpaths)->len)
            return (1);
        spurpaths++;
    }
    return (0);
}
