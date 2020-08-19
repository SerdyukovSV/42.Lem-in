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

static t_path   *reconstruct_path(t_lemin *lemin)
{
    // printf("reconstruct_path\n");
    t_path  *path;
    int     fin;

    if (!(path = malloc(sizeof(t_path))))
        return (NULL);
    fin = lemin->final;
    path->len = 0;
    path->node[path->len++] = lemin->node[fin];
    while (lemin->parent[fin] != -1)
    {
        fin= lemin->parent[fin];
        path->node[path->len++] = lemin->node[fin];
    }
    path->node[path->len] = NULL;
    return (path);
}

static void     add_queue(t_lemin *lemin, t_node *src, t_node *dst)
{
    // printf("\e[92madd_queue\e[0m\n");
    t_node **node;

    node = lemin->node;
    if(lemin->links->visited[dst->id] == 0)
    {
        // printf("dst = %s\n", node[dst->id]->name);
        if (!node[src->id]->in_path)
        {
            // printf("step_1\n");
            // printf("in_path = %d | is_start = %d\n", node[dst->id]->in_path, node[dst->id]->is_start);
            if (node[dst->id]->in_path && !node[dst->id]->is_start && dst->id != lemin->final)
            {
                // printf("step_1.2\n");
                lemin->parent[dst->id] = src->id;
                lemin->links->visited[dst->id] = 1;

                lemin->parent[node[dst->id]->previous] = dst->id;
                lemin->links->visited[node[dst->id]->previous] = 1;
                enqueue(lemin->queue, node[node[dst->id]->previous]);
            }
            else if (!node[dst->id]->in_path)
            {
                // printf("step_1.3\n");
                enqueue(lemin->queue, node[dst->id]);
                lemin->links->visited[dst->id] = 1;
                lemin->parent[dst->id] = src->id;
            }
        }
        else if (dst->capacity >= 1)
        {
            // printf("step_2\n");
            // printf("[%s]->capacity = %d\n", dst->name, dst->capacity);
            enqueue(lemin->queue, node[dst->id]);
            lemin->links->visited[dst->id] = 1;
            lemin->parent[dst->id] = src->id;
        }
    }
}

static t_path   *search_path(t_lemin *lemin, t_node *src)
{
    // printf("search_path\n");
    t_node      *tmp;

    enqueue(lemin->queue, src);
    lemin->parent[src->id] = -1;
    while(lemin->queue->rear != -1)
    {
        src = dequeue(lemin->queue);
        // printf("\e[93msrc = %s | %d\e[0m\n", src->name, src->id);
        lemin->links->visited[src->id] = 1;
        tmp = lemin->links->adjace[src->id];
        // printf("step_1\n");
        while(tmp)
        {
            if (tmp->id == lemin->final)
            {
                // printf("step_2\n");
                lemin->parent[tmp->id] = src->id;
                return (reconstruct_path(lemin));
            }
            add_queue(lemin, src, tmp);
            tmp = tmp->next;
        }
    }
    return (NULL);
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
    print_paths_all(paths);
    printf("\n");
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
    sort_unique(lemin->paths);
}
