#include "../includes/lemin.h"

// static void path_del(t_node *path)
// {
//     // printf("path_del\n");
//     t_node *tmp;

//     while (path)
//     {
//         tmp = path;
//         path = path->next;
//         free(tmp);
//     }
// }

static int cmp_paths(t_node *current, t_node *compar, int fin)
{
    // printf("\e[91mcmp_paths\e[0m\n");
    t_node  *tmp;
    int     i;
    int     j;

    i = path_len(current);
    if (!compar)
        return (0);
    j = 0;
    while (current)
    {
        tmp = compar->next;
        while (tmp->next && current->id != tmp->id)
            tmp = tmp->next;
        if (tmp->id != fin)
            j++;
        current = current->next;
    }
    if (i == j)
        return (1);
    else if (j)
        return (2);
    return (0);
}

// static t_node **cmp(t_lemin *lemin, t_node **paths)
// {
//     t_node  **newpaths;
//     int     tmp[300] = {0};
//     int     len;
//     int     i;
//     int     j;
//     int     k;

//     i = 0;
//     len = 0;
//     newpaths = NULL;
//     while (paths[len])
//         len++;
//     while (i < len)
//     {
//         j = i;
//         k = 0;
//         ft_bzero(tmp, sizeof(int) * 300);
//         while (++j < len && paths[i])
//         {
//             if (cmp_paths(paths[i]->next, paths[j], lemin->rooms->end->id) == 2)
//                 tmp[k++] = j;
//         }
//         j = 0;
//         while (j < k && k > 1)
//         {
//             if (tmp[j + 1])
//             {
//                 if (cmp_paths(paths[tmp[j]]->next, paths[tmp[j + 1]], lemin->rooms->end->id) == 2)
//                 {
//                     paths[tmp[j]] = NULL;
//                     paths[tmp[j + 1]] = NULL;
//                 }
//             }
//             else
//                 paths[tmp[j]] = NULL;
//             j++;
//         }
//         if (k == 1)
//             paths[tmp[k]] = NULL;
//         i++;
//     }
//     i = 0;
//     j = 0;
//     while (i < len)
//     {
//         if (paths[i])
//             newpaths[j++] = paths[i];
//         i++;
//     }
//     return (newpaths);
// }

t_node **new_paths(t_lemin *lemin, t_node **paths)
{
    // printf("\e[91mnew_paths\e[0m\n");
    t_node  **new_p;
    int     len;
    int     i;
    int     j;
    int     k;

    i = 0;
    while (paths[i])
        i++;
    len = i;
    i = 0;
    k = 0;
    new_p = creat_paths(1000);
    while (i < len)
    {
        j = i;
        while (++j < len && paths[i])
        {
            if (cmp_paths(paths[i]->next, paths[j], lemin->rooms->end->id) == 1)
            {
                // path_del(paths[j]);
                paths[j] = NULL;
            }
        }
        if (paths[i])
            new_p[k++] = paths[i];
        i++;
    }
    t_node *tmp;
    i = -1;
    while (new_p[++i])
    {
        j = -1;
        while (new_p[++j])
        {
            if (path_len(new_p[j]) > path_len(new_p[j + 1]) && path_len(new_p[j + 1]) > 0)
            {
                tmp = new_p[j];
                new_p[j] = new_p[j + 1];
                new_p[j + 1] = tmp;
            }
        }
    }

    return (/* cmp(lemin, new_p) */new_p);
}
