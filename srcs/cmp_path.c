#include "../includes/lemin.h"

t_node **cmp_paths(t_rooms *rooms, t_node **paths)
{
    t_node  *sh_path;
    t_node  **new_paths;
    t_node  *tmp;
    int     i;
    int     k;

    i = 0;
    k = -1;
    new_paths = malloc(sizeof(t_node *) * 100);
    while (++k < 100)
        new_paths[k] = NULL;
    k = 0;
    new_paths[k] = paths[0]->next;
    while (paths[++i])
    {
        sh_path = paths[0]->next;
        while (sh_path)
        {
            tmp = paths[i]->next;
            while (tmp && sh_path->id != tmp->id)
                tmp = tmp->next;
            if (tmp->id == rooms->end->id)
                sh_path = sh_path->next;
            else
                break ;
        }
        if (!sh_path)
            new_paths[++k] = paths[i];
    }
    return (new_paths);
}