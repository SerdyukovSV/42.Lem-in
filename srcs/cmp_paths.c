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
                if (newpath->path[j] == (*spurpaths)->path[i]/*  && newpath->path[j] != lemin->start && newpath->path[j] != lemin->final */)
                {
                    // return (1);
                    equal++;
                }
        }
        if (equal == (*spurpaths)->len)
            return (1);
        spurpaths++;
    }
    return (0);
}

int match_paths(t_path **paths, t_path *current, int fin)
{
    int equal;
    int i;
    int j;
    int k;
    int bl;

    equal = 0;
    bl = 0;
    i = 1;
    while (i < current->len && current->path[i] != fin)
    {
        j = 0;
        while (paths[j])
        {
            k = -1;
            while (++k < paths[j]->len && paths[j] != current)
            {
                if (paths[j]->path[k] == current->path[i])
                {
                    equal++;
                    bl = 1;
                    break ;
                }
            }
            if (bl == 1)
            {
                bl = 0;
                break ;
            }
            j++;
        }
        i++;
    }
    return (equal);
}

int sortpaths(t_lemin *lemin)
{
    printf("sortpaths\n");
    t_path *tmp[lemin->size][100];
    t_path **paths;
    t_node *node;
    int i;
    int j;
    int k;

    j = 0;
    node = lemin->links->adjace[lemin->start];
    while (node)
    {
        k = 0;
        i = -1;
        paths = lemin->shortpaths;
        while (paths[++i])
        {
            if (paths[i]->path[1] == node->id)
                tmp[j][k++] = paths[i];
        }
        i = -1;
        paths = lemin->spurpaths;
        while (paths[++i])
        {
            if (paths[i]->path[1] == node->id)
                tmp[j][k++] = paths[i];
        }
        node = node->next;
        tmp[j][k] = NULL;
        j++;
    }
    i = -1;
    while (++i < lemin->size && tmp[i])
    {
        // printf("\e[93msize = %d\e[0m\n", i);
        j = 0;
        if (tmp[i][j])
            printf("%s\n", lemin->rooms->hroom[tmp[i][j]->path[1]]->name);
        while (tmp[i][j])
        {
            k = -1;
            printf("Path[%d][%d][%d]:", i, tmp[i][j]->len, match_paths(tmp[i], tmp[i][j], lemin->final));
            while (++k < tmp[i][j]->len)
                printf(" %s", lemin->rooms->hroom[tmp[i][j]->path[k]]->name);
            printf("\n");
            j++;
        }
    }
    return (1);
}
