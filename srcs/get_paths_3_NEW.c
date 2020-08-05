#include "../includes/lemin.h"

static void     possible_paths(t_lemin *lemin, t_path *rootpath)
{
    t_node  *tmp;
    int     i;

    i = -1;
    lemin->possible = 0;
    while (++i < rootpath->len)
    {
        tmp = lemin->links->adjace[rootpath->path[i]];
        while (tmp)
        {
            lemin->possible++;
            tmp = tmp->next;
        }
    }
}

static void     setlink_spur(t_lemin *lemin, t_path *spurpaths, int root, int set)
{
    // printf("\e[93msetlink_spur\e[0m\n");
    t_node  *tmp;
    int     i;

    i = 0;
    tmp = lemin->links->adjace[root];
    while (i < spurpaths->len - 1)
    {
        // printf(" %s", lemin->rooms->hroom[spurpaths->path[i]]->name);
        if (spurpaths->path[i++] == root)
        {
            while (tmp && tmp->id != spurpaths->path[i])
                tmp = tmp->next;
            // printf("\n%s = %d\n", tmp->name, tmp->path);
            if (tmp && tmp->id == spurpaths->path[i])
                tmp->path = set;
            // printf("%s = %d\n", tmp->name, tmp->path);
            break ;
        }
    }
}

static void     setlink_root(t_lemin *lemin, int *rootpath, int set)
{
    // printf("\e[93msetlink_root\e[0m\n");
    t_node  *tmp;

    tmp = lemin->links->adjace[rootpath[0]];
    // printf("root[0] = %s\n", lemin->rooms->hroom[rootpath[0]]->name);
    // printf("root[1] = %s\n", lemin->rooms->hroom[rootpath[1]]->name);
    while (tmp && tmp->id != rootpath[1])
        tmp = tmp->next;
    if (tmp && tmp->id == rootpath[1])
    {
        // printf("%s = %d\n", tmp->name, tmp->path);
        tmp->path = set;
        // printf("%s = %d\n", tmp->name, tmp->path);
    }
}

static void     setvertex(t_lemin *lemin, int vertex, int set)
{
    // printf("setvertex\n");
    t_node  *src;
    t_node  *adj;
    int i;

    i = -1;
    // printf("vertex = %s\n", lemin->rooms->hroom[vertex]->name);
    src = lemin->links->adjace[vertex];
    while (src)
    {
        // printf("src = %s\n", lemin->rooms->hroom[src->id]->name);
        adj = lemin->links->adjace[src->id];
        while (adj)
        {
            if (adj->id == vertex)
            {
                // printf("%s = %d\n", adj->name, adj->path);
                adj->path = set;
                // printf("%s = %d\n", adj->name, adj->path);
                break ;
            }
            adj = adj->next;
        }
        src = src->next;
    }
}

static void     rebuildgraph(t_lemin *lemin, t_shortpath *shortpath, int set)
{
    // printf("rebuildgraph\n");
    t_path  *rootpath;
    t_path  **spurpaths;
    int     i;
    int     j;

    i = 0;
    rootpath = shortpath->rootpath;
    spurpaths = shortpath->spurpaths;
    while (i < rootpath->len && rootpath->path[i + 1] != -1)
    {
        setlink_root(lemin, &rootpath->path[i], set);
        j = -1;
        while (spurpaths[++j])
            setlink_spur(lemin, spurpaths[j], rootpath->path[i], set);
        setvertex(lemin, rootpath->path[i], set);
        i++;
    }
}

static void     search_path(t_lemin *lem, t_queue *queue, int *parent, int current)
{
    // printf("search_path\n");
    t_node      *tmp;

    // ft_bzero(lem->links->visited, sizeof(int) * lem->rooms->total);
    ft_bzero(parent, sizeof(int) * lem->rooms->total);
    enqueue(queue, current);
    parent[current] = -1;
    while(queue->rear != -1)
    {
        current = dequeue(queue);
        lem->links->visited[current] = 1;
        tmp = lem->links->adjace[current];
        while(tmp)
        {
            if (tmp->path == 0)
            {
                if(lem->links->visited[tmp->id] == 0)
                {
                    enqueue(queue, tmp->id);
                    lem->links->visited[tmp->id] = 1;
                    parent[tmp->id] = current;
                }
            }
            tmp = tmp->next;
        }
    }
}

static t_path   *get_newpath(int *parent, int fin)
{
    // printf("\e[92mget_newpath\e[0m\n");
    t_path  *newpath;
    int     tmp[256];
    int     i;

    if (!(newpath = malloc(sizeof(t_path))))
        return (NULL);
    i = 0;
    newpath->dupl = -1;
    ft_memset(tmp, -1, sizeof(int) * 256);
    ft_memset(newpath->path, -1, sizeof(int) * 256);
    tmp[i] = fin;
    while (parent[fin] != -1)
    {
        fin= parent[fin];
        tmp[++i] = fin;
    }
    newpath->len = -1;
    while (++newpath->len <= i)
        newpath->path[newpath->len] = tmp[i - newpath->len];
    return (newpath);
}

static t_path   *pathjoin(t_path *rootpath, t_path *newpath, int cur)
{
    // printf("\e[92mpathjoin\e[0m\n");
    t_path  *tmp;
    int     i;
    int     j;

    tmp = malloc(sizeof(t_path));
    ft_memset(tmp->path, -1, sizeof(int) * 256);
    tmp->len = 0;
    tmp->dupl = -1;
    if (newpath)
    {
        i = -1;
        while (rootpath->path[++i] != cur)
            tmp->path[i] = rootpath->path[i];
        j = 0;
        while (j < newpath->len)
            tmp->path[i++] = newpath->path[j++];
        tmp->len = i;
        free(newpath);
    }
    return (tmp);
}

static void     get_spurpaths(t_lemin *lemin, t_shortpath *shortpath, int *parent)
{
    // printf("\e[91mget_spurpaths\e[0m\n");
    t_path  **spurpaths;
    t_path  *rootpath;
    t_path  *new;
    int     i;
    int     j;

    j = 1;
    rootpath = shortpath->rootpath;
    spurpaths = shortpath->spurpaths;
    while (lemin->possible > 0)
    {
        i = -1;
        while (++i < rootpath->len && rootpath->path[i + 1] != -1)
        {
            ft_bzero(lemin->links->visited, sizeof(int) * lemin->rooms->total);
            setvertex(lemin, rootpath->path[i], DEL);
            setlink_root(lemin, &rootpath->path[i], DEL);
            search_path(lemin, creat_queue(), parent, rootpath->path[i]);
            if (lemin->links->visited[lemin->final])
            {
                new = get_newpath(parent, lemin->final);
                new = pathjoin(rootpath, new, rootpath->path[i]);
                if (!cmp_paths(spurpaths, new, lemin) && new->len < 90)
                {
                    spurpaths[j++] = new;
                    setlink_spur(lemin, spurpaths[j - 1], rootpath->path[i], DEL);
                }
            }
            lemin->possible--;
        }
    }
    rebuildgraph(lemin, shortpath, SET);
}

static t_path   *get_rootpath(t_lemin *lemin, t_node **start)
{
    // printf("\e[92mget_rootpath\e[0m\n");
    int parent[lemin->rooms->total];
    t_path *new;

    ft_bzero(lemin->links->visited, sizeof(int) * lemin->rooms->total);
    search_path(lemin, creat_queue(), parent, (*start)->id);
    if (lemin->links->visited[lemin->final])
    {
        if ((new = get_newpath(parent, lemin->final))->len < 90)
            return (new);
        else
        {
            (*start) = (*start)->next;
            return (get_rootpath(lemin, start));
        }
    }
    else
        return (get_rootpath(lemin, start));
}

static void     get_shortpaths(t_lemin *lemin, int *parent, t_node *start)
{
    // printf("\e[92mget_shortpaths\e[0m\n");
    t_shortpath **shortpaths;
    int         i;

    i = 0;
    shortpaths = malloc(sizeof(t_shortpath *) * lemin->size + 1);
    ft_memset(shortpaths, 0, sizeof(t_shortpath *) * (lemin->size + 1));
    while (start)
    {
        shortpaths[i] = (t_shortpath *)malloc(sizeof(t_shortpath));
        shortpaths[i]->rootpath = get_rootpath(lemin, &start);
        shortpaths[i]->spurpaths = malloc(sizeof(t_path *) * 100);
        ft_memset(shortpaths[i]->spurpaths, 0, sizeof(t_path *) * 100);
        shortpaths[i]->spurpaths[0] = shortpaths[i]->rootpath;
        possible_paths(lemin, shortpaths[i]->rootpath);
        get_spurpaths(lemin, shortpaths[i], parent);
        start = start->next;
        i++;
    }
    lemin->shortpaths = shortpaths;
}

void        get_paths(t_lemin* lemin)
{
    // printf("\e[92mget_paths\e[0m\n");
    int parent[lemin->rooms->total];
    t_node  *start;

    start = lemin->links->adjace[lemin->start];
    setvertex(lemin, lemin->start, DEL);
    get_shortpaths(lemin, parent, start);

    // printf("\e[93mEND\e[0m\n");
    sort_spurpaths(lemin->shortpaths);
    sort_rootpaths(lemin->shortpaths);
    // print_paths_2(lemin);
}
