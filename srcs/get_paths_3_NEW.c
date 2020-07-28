#include "../includes/lemin.h"

static int      get_count(t_path **paths)
{
    // printf("get_count\n");
    int i;

    i = 0;
    while (paths[i])
        i++;
    return (i);
}

static void     sort_spurpaths(t_path **paths)
{
    // printf("sortpaths\n");
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

static int      setlink(t_lemin *lemin, int curr, int next, int set)
{
    // system("sleep 0.05");
    printf("\e[93msetlink\e[0m\n");
    // printf("setlink = %s | %s(%d)-%s(%d)\n", set ? "OFF" : "ON", lemin->rooms->hroom[curr]->name, curr, lemin->rooms->hroom[next]->name, next);
    int     i;
    int     j;
    t_node  *tmp;
    t_path  **shortpaths;

    i = -1;
    shortpaths = lemin->shortpaths;
    while (shortpaths[++i])
    {
        j = 0;
        while (j < shortpaths[i]->len)
        {
            if (shortpaths[i]->path[j++] == curr)
            {
                next = shortpaths[i]->path[j];
                tmp = lemin->links->adjace[curr];
                while (tmp)
                {
                    if (tmp->id == next)
                    {
                        printf("%s = %d\n", tmp->name, set);
                        tmp->path = set;
                        break ;
                    }
                    tmp = tmp->next;
                }
                break ;
            }
        }
    }
    return (0);
}

static int      setvertex(t_lemin *lemin, int *path, int current)
{
    // printf("setvertex | %s - %s\n", lemin->rooms->hroom[path[0]]->name, lemin->rooms->hroom[current]->name);
    int i;

    i = -1;
    while (path[++i] != current)
    {
        // printf("%s - ", lemin->rooms->hroom[path[i]]->name);
        lemin->links->visited[path[i]] = 1;
    }
    i = -1;
    while (lemin->visitroom[++i] != -1)
    {
        lemin->links->visited[lemin->visitroom[i]] = 1;
        // printf("\e[96mlinks->visited[%d] = %d\e[0m\n", lemin->visitroom[i], lemin->links->visited[lemin->visitroom[i]]);
    }
    // printf("\n");
    return (i);
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

static void     rebuildgraph(t_lemin *lemin, t_path *shortpath, int set)
{
    printf("rebuildgraph\n");
    int *tmp;
    int i;

    i = 0;
    tmp = shortpath->path;
    while (tmp[i + 1] != -1)
    {
        setlink(lemin, tmp[i], tmp[i + 1], set);
        i++;
    }
}

static int      get_newshort(t_path **shortpaths, t_path **spurpaths, t_lemin *lemin)
{
    printf("get_newshort\n");
    int     i;
    int     j;
    int     k;
    int     *edge;

    i = 0;
    edge = NULL;
    // j = get_count(spurpaths);
    k = get_count(shortpaths);
    cmp_paths(shortpaths, spurpaths[i], lemin);
    sort_spurpaths(spurpaths);
    shortpaths[k] = spurpaths[i];
    j = 0;
    while (i < k)
    {
        // if (!cmp_paths(shortpaths, spurpaths[i], lemin))
        // {
        //     shortpaths[k] = spurpaths[i];
        //     while (i < j)
        //     {
        //         spurpaths[i] = spurpaths[i + 1];
        //         spurpaths[i + 1] = NULL;
        //         i++;
        //     }
        //     return (1);
        // }
        if (spurpaths[j] && spurpaths[j]->path[1] == shortpaths[i]->path[1])
        {
            j++;
            i = 0;
        }
        i++;
    }
    i = get_count(spurpaths);
    if (j < i)
    {
        shortpaths[k] = spurpaths[j];
        while (j < i)
        {
            spurpaths[j] = spurpaths[j + 1];
            spurpaths[j + 1] = NULL;
            j++;
        }
    }
    else
    {
        shortpaths[k] = spurpaths[0];
        i = -1;
        while (++i < j)
        {
            spurpaths[i] = spurpaths[i + 1];
            spurpaths[i + 1] = NULL;
        }
    }
    return (1);
}

static t_path   *get_newpath(int *parent, int fin)
{
    printf("\e[92mget_newpath\e[0m\n");
    t_path  *newpath;
    int     tmp[256];
    int     i;

    if (!(newpath = malloc(sizeof(t_path))))
        return (NULL);
    i = 0;
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
    printf("\e[92mpathjoin\e[0m\n");
    t_path  *tmp;
    int     i;
    int     j;

    tmp = malloc(sizeof(t_path));
    ft_memset(tmp->path, -1, sizeof(int) * 256);
    tmp->len = 0;
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

static int      get_spurpaths(t_lemin *lemin, t_path *rootpath, int *parent)
{
    // printf("\e[91mget_spurpaths\e[0m\n");
    t_path  *new;
    t_path **spurpaths;
    int     *tmp;
    int     i;

    i = -1;
    tmp = rootpath->path;
    spurpaths = lemin->spurpaths;
    while (tmp[++i + 1] != -1)
    {
        ft_bzero(lemin->links->visited, sizeof(int) * lemin->rooms->total);
        setlink(lemin, tmp[i], tmp[i + 1], DEL);
        setvertex(lemin, rootpath->path, tmp[i]);
        search_path(lemin, creat_queue(), parent, tmp[i]);
        if (lemin->links->visited[lemin->final])
        {
            if ((new = get_newpath(parent, lemin->final)))
            {
                if ((new = pathjoin(rootpath, new, tmp[i]))->len < 256)
                {
                    if (!cmp_paths(lemin->shortpaths, new, lemin) && !cmp_paths(spurpaths, new, lemin))
                    {
                        // printf("\e[94madd path\e[0m\n");
                        spurpaths[get_count(spurpaths)] = new;
                        // print_paths(new, lemin);
                    }
                }
            }
        }
        // setlink(lemin, tmp[i], tmp[i + 1], SET);
    }
    rebuildgraph(lemin, rootpath, SET);
    return (1);
}

static void     get_shortpaths(t_lemin *lemin, int *parent)
{
    printf("\e[92mget_shortpaths\e[0m\n");
    t_path  **shortpaths;
    t_path  **spurpaths;
    int     prim;
    int     i;

    shortpaths = lemin->shortpaths;
    spurpaths = lemin->spurpaths;
    i = 0;
    prim = 45;
    // print_paths_2(lemin);
    while (get_spurpaths(lemin, shortpaths[i], parent))
    {
        // if (lemin->count < get_count(spurpaths))
        // {
        //     lemin->count = get_count(spurpaths);
        //     // rebuildgraph(lemin, shortpaths[i], DEL);
        get_newshort(shortpaths, spurpaths, lemin);
        // printf("\e[96mstartroom = %s(%d)\e[0m\n", lemin->rooms->hroom[shortpaths[i]->path[1]]->name, lemin->rooms->hroom[shortpaths[i]->path[1]]->id);
        lemin->visitroom[i] = shortpaths[i]->path[1];
        // printf("\e[96mvisitroom[%d] = %d\e[0m\n", i, lemin->visitroom[i]);
        i++;
            // if (get_newshort(shortpaths, spurpaths, lemin))
                /* rebuildgraph(lemin, shortpaths[++i], SET) */;
        // }
        // else
        // {
        //     printf("\e[94mbreak\e[0m\n");
        //     break ;
        // }
        // print_paths_2(lemin);
        if (!prim--)
            break ;
    }
}

void        get_paths(t_lemin* lemin)
{
    // printf("\e[92mget_paths\e[0m\n");
    int parent[lemin->rooms->total];
    int visitroom[lemin->size + 1000];

    // printf("size = %d\n", lemin->size);
    ft_memset(visitroom, -1, sizeof(visitroom));
    lemin->visitroom = visitroom;
    lemin->primpath = NULL;
    lemin->spurpaths = malloc(sizeof(t_path *) * 500);
    lemin->shortpaths = malloc(sizeof(t_path *) * 100);
    if (!lemin->shortpaths || !lemin->spurpaths)
        ft_error(ERR);
    ft_bzero(lemin->links->visited, sizeof(int) * lemin->rooms->total);
    search_path(lemin, creat_queue(), parent, lemin->start);
    if (lemin->links->visited[lemin->final])
    {
        lemin->primpath = get_newpath(parent, lemin->final);
        lemin->shortpaths[0] = lemin->primpath;
        get_shortpaths(lemin, parent);
    }
    print_paths_2(lemin);
}
