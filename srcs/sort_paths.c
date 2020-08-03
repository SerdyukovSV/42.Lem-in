#include "../includes/lemin.h"

void     sort_spurpaths(t_shortpath **shortpaths)
{
    // printf("sort_spurpaths\n");
    t_path  **spurpath;
    t_path  *tmp;
    int     i;
    int     j;
    int     k;

    i = -1;
    while (shortpaths[++i])
    {
        spurpath = shortpaths[i]->spurpaths;
        j = -1;
        while (spurpath[++j])
        {
            k = -1;
            while (spurpath[++k])
            {
                if (spurpath[k + 1] && spurpath[k]->len > spurpath[k + 1]->len)
                {
                    tmp = spurpath[k];
                    spurpath[k] = spurpath[k + 1];
                    spurpath[k + 1] = tmp;
                }
            }
        }
    }
}

void     sort_rootpaths(t_shortpath **shortpaths)
{
    // printf("sort_spurpaths\n");
    t_shortpath  *tmp;
    int     i;
    int     j;

    i = -1;
    while (shortpaths[++i])
    {
        j = -1;
        while (shortpaths[++j])
        {
            if (shortpaths[j + 1] && shortpaths[j]->rootpath->len > shortpaths[j + 1]->rootpath->len)
            {
                tmp = shortpaths[j];
                shortpaths[j] = shortpaths[j + 1];
                shortpaths[j + 1] = tmp;
            }
        }
    }
}