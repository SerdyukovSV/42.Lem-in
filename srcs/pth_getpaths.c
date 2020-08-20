#include "../includes/lemin.h"

static int      is_best_paths(t_lemin *lemin, t_path **paths)
{
    // printf("is_best_paths\n");
    int f1;
    int f2;

    if (!paths[0] || !lemin->paths[0])
        return (!paths[0] ? 0 : 1);
    f1 = get_flow(lemin->paths, lemin->ants);
    f2 = get_flow(paths, lemin->ants);
    if (f2 <= f1)
        return (1);
    return (0);
}

static t_path   *add_path(t_lemin *lemin, t_node *current)
{
    // printf("add_path\n");
    t_path *path;

    if (!(path = malloc(sizeof(t_path))))
        ft_error(ERR);
    path->len = 0;
    path->node[path->len++] = lemin->rooms->start;
    path->node[path->len++] = current;
    // printf("node = %s\n", lemin->node[start->id]->name);
    current = lemin->links->adjace[current->id];
    while (current)
    {
        if (current->capacity == 0)
        {
            path->node[path->len++] = current;
            path->node[path->len] = NULL;
            if (current->id == lemin->final)
                return (path);
            current = lemin->links->adjace[current->id];
        }
        else
            current = current->next;
    }
    free(path);
    return (NULL);
}

static t_path   **get_newpaths(t_lemin *lemin, t_path  **paths)
{
    // printf("get_newtpaths\n");
    t_node  *start;
    int     i;

    i = 0;
    // ft_bzero(paths, sizeof(t_path *) * (lemin->size + 1));
    start = lemin->links->adjace[lemin->start];
    while (start)
    {
        if ((paths[i] = add_path(lemin, start)))
            i++;
        start = start->next;
    }
    paths[i] = NULL;
    if (is_best_paths(lemin, paths))
        return (paths);
    return (NULL);
}

static void     get_shortpaths(t_lemin *lemin, t_node *start)
{
    // printf("get_shortpaths\n");
    t_path  *paths[lemin->size + 1];
    t_path  *tmp;
    int     size;

    size = sizeof(t_path *) * (lemin->size + 1);
    // printf("start = %s\n", start->name);
    lemin->queue->front = -1;
    lemin->queue->rear = -1;
    ft_bzero(lemin->parent, sizeof(int) * lemin->rooms->total);
    ft_bzero(lemin->links->visited, sizeof(int) * lemin->rooms->total);
    if ((tmp = search_path(lemin, start)))
    {
        rebuildgraph(lemin, tmp, SET);
        if (get_newpaths(lemin, paths))
        {
            ft_memcpy(lemin->paths, paths, size);
            set_attributes(lemin, lemin->paths);
        }
        else
            return ;
            // rebuildgraph(lemin, tmp, DEL);
        ///// free path from reconstruct_path!!!!!!!!!!
        get_shortpaths(lemin, lemin->rooms->start);
    }
    else
        return ;
}

void            get_paths(t_lemin* lemin)
{
    int     parent[lemin->rooms->total];
    t_node  *start;
    t_queue queue;

    lemin->queue = &queue;
    lemin->parent = parent;
    if (!(lemin->paths = malloc(sizeof(t_path *) * (lemin->size + 1))))
        ft_error(ERR);
    ft_bzero(lemin->paths, sizeof(t_path *) * lemin->size * 1);
    start = lemin->links->adjace[lemin->start];
    while (start)
    {
        lemin->node[start->id]->is_start = 1;
        start = start->next;
    }
    get_shortpaths(lemin, lemin->rooms->start);
    sort_paths(lemin->paths);
}
