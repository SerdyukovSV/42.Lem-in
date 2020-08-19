#include "../includes/lemin.h"

int     cmp_paths(t_path **spurpaths, t_path *newpath)
{
    int     i;
    int     j;
    int     equal;

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

// void    sort_spurpaths(t_shortpath **shortpaths)
// {
//     t_path  **spurpath;
//     t_path  *tmp;
//     int     i;
//     int     j;
//     int     k;

//     i = -1;
//     while (shortpaths[++i])
//     {
//         spurpath = shortpaths[i]->spurpaths;
//         j = -1;
//         while (spurpath[++j])
//         {
//             k = -1;
//             while (spurpath[++k])
//             {
//                 if (spurpath[k + 1] && spurpath[k]->len > spurpath[k + 1]->len)
//                 {
//                     tmp = spurpath[k];
//                     spurpath[k] = spurpath[k + 1];
//                     spurpath[k + 1] = tmp;
//                 }
//             }
//         }
//     }
// }

// void    sort_rootpaths(t_shortpath **shortpaths)
// {
//     t_shortpath  *tmp;
//     int     i;
//     int     j;

//     i = -1;
//     while (shortpaths[++i])
//     {
//         j = -1;
//         while (shortpaths[++j])
//         {
//             if (shortpaths[j + 1] && shortpaths[j]->rootpath->len > shortpaths[j + 1]->rootpath->len)
//             {
//                 tmp = shortpaths[j];
//                 shortpaths[j] = shortpaths[j + 1];
//                 shortpaths[j + 1] = tmp;
//             }
//         }
//     }
// }

void    sort_unique(t_path **paths)
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
            if (paths[j + 1] && paths[j]->len > paths[j + 1]->len)
            {
                tmp = paths[j];
                paths[j] = paths[j + 1];
                paths[j + 1] = tmp;
            }
        }
    }
}