#include "../includes/lemin.h"

static void freepath(t_node *path)
{
    printf("\e[91mfreepath\e[0m\n");
    t_node  *tmp;

    while (path)
    {
        // printf("path = %s\n", path ? "" : "(null)");
        // printf("path->name = %s\n", path->name);
        tmp = path;
        path = path->next;
        free(tmp);
    }
    tmp = NULL;
}

static int  get_countpaths(t_node **paths)
{
    // printf("get_countpaths\n");
    int i;

    i = 0;
    while (paths[i])
        i++;
    return (i);
}

static void sortpaths(t_node **paths)
{
    // printf("sortpaths\n");
    t_node  *tmp;
    int     i;
    int     j;

    i = -1;
    while (paths[++i])
    {
        j = -1;
        while (paths[++j])
        {
            if (paths[j + 1] && path_len(paths[j]) > path_len(paths[j + 1]))
            {
                // printf("\e[93mstep sort | j = %d\e[0m\n", j);
                tmp = paths[j];
                paths[j] = paths[j + 1];
                paths[j + 1] = tmp;
            }
        }
    }
}

static int  cmp_paths(t_node *shortpath, t_node *spurpath)
{
    // printf("\e[94mcmp_paths\e[0m\n");
    t_node  *tmp;
    int     i;
    int     j;

    j = 0;
    i = path_len(shortpath);
    while (shortpath)
    {
        tmp = spurpath;
        while (tmp)
        {
            if (shortpath->id == tmp->id)
            {
                j++;
                break ;
            }
            tmp = tmp->next;
        }
        shortpath = shortpath->next;
    }
    if (i == j)
        return (1);
    return (0);
}

static int  spurcmp(t_lemin *lemin, t_node **spurpaths, int *parent)
{
    // printf("\e[92mspurcmp\e[0m\n");
    int     path[512];
    t_node  *tmp;
    int     i;
    int     k;
    int     j;

    i = 0;
    ft_bzero(path, sizeof(int) * 512);
    k = lemin->rooms->end->id;
    if (lemin->links->visited[k])
    {
        // printf("step_1\n");
        while (parent[k] != -1)
        {
            if (parent[k] != lemin->rooms->start->id)
                path[i++] = parent[k];
            k = parent[k];
        }
        if ((i + 2) >= 128)
            return (128);
        // printf("spurpaths = %s\n", spurpaths[0] == NULL ? "(null)" : "true");
        k = -1;
        while (spurpaths[++k])
        {
            // printf("spurpaths[%d]\n", k);
            tmp = spurpaths[k]->next;
            while (tmp)
            {
                j = -1;
                while (++j < i)
                    if (path[j] == tmp->id)
                        return (1);
                tmp = tmp->next->next ? tmp->next : NULL;
            }
        }
        return (0);
    }
    return (1);
}

static int  setlink(t_links *links, t_node *node, int set)
{
    // printf("setlink = %d | %s\n", set, node->name);
    t_node  *tmp;

    if (node->next)
    {
        tmp = links->adjace[node->id];
        // t_node *p = links->adjace[node->id];
        // while (p)
        // {
        //     printf("\e[94m%s[%d]\t", p->name, p->path);
        //     p = p->next;
        // }
        // printf("\e[0m\n");
        while (tmp)
        {
            if (tmp->id == node->next->id)
            {
                tmp->path = set;
                // t_node *p = links->adjace[node->id];
                // while (p)
                // {
                //     printf("\e[94m%s[%d]\t", p->name, p->path);
                //     p = p->next;
                // }
                // printf("\e[0m\n");
                return (1);
            }
            tmp = tmp->next;
        }
    }
    return (0);
}

static void add_path(t_lemin *lemin, t_node **paths, int *parent)
{
    // printf("add_path\n");
    t_node      **rooms;
    t_node      *tmp;
    int         final;
    int         count;

    rooms = lemin->rooms->hroom;
    final = lemin->rooms->end->id;
    count = get_countpaths(paths);
    // printf("count = %d\n", count);
    if (!lemin->links->visited[final])
    {
        printf("\e[91mno path\e[0m\n");
        return ;
    }
    paths[count] = room_dup(rooms[final]);
    while (parent[final] != -1)
    {
        tmp = room_dup(rooms[parent[final]]);
        tmp->next = paths[count];
        paths[count] = tmp;
        final = parent[final];
    }
}

static void search_path(t_lemin *lem, t_queue *queue, int *parent, int current)
{
    // printf("search_path\n");
    t_node      *tmp;

    ft_bzero(lem->links->visited, sizeof(int) * lem->rooms->total);
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

static void rebuildgraph(t_lemin *lemin, t_node *shortpath, int set)
{
    printf("rebuildgraph\n");
    int final;

    final = lemin->rooms->end->id;
    while (shortpath)
    {
        setlink(lemin->links, shortpath, set);
        shortpath = shortpath->next;
    }
}

static t_node *get_shortspurpath(t_node **spurpaths, t_node *shortpath)
{
    printf("get_shortspurpath\n");
    t_node  *tmp;
    int     i;

    i = 0;
    sortpaths(spurpaths);
    tmp = spurpaths[i];
    if (cmp_paths(shortpath, spurpaths[i]))
    {
        // print_paths(spurpaths[i], i);
        freepath(spurpaths[i]);
        tmp = NULL;
    }
    spurpaths[i] = NULL;
    while (spurpaths[i + 1])
    {
        spurpaths[i] = spurpaths[i + 1];
        spurpaths[i + 1] = NULL;
        i++;
    }
    return (tmp);
}

static int get_spurpaths(t_lemin *lemin, t_node *shortpath, int *parent)
{
    printf("\e[92mget_spurpaths\e[0m\n");
    int     start;
    int     ret;
    t_node  *tmp;

    start = lemin->rooms->start->id;
    tmp = shortpath;
    while (setlink(lemin->links, tmp, DEL))
    {
        search_path(lemin, creat_queue(), parent, start);
        if ((ret = spurcmp(lemin, lemin->spurpath, parent)) == 0)
        {
            add_path(lemin, lemin->spurpath, parent);
        }
        else if (ret >= 128)
            return (0);
        setlink(lemin->links, tmp, SET);
        tmp = tmp->next;
    }
    ////////////////////
    // printf("\e[92m\n");
    // print_paths_2(lemin->spurpath);
    // printf("\e[0m\n");
    ////////////////////
    rebuildgraph(lemin, shortpath, DEL);
    return (1);
    // get_shortpaths(lemin, parent, lemin->rooms->end->id);
}

static void get_shortpaths(t_lemin *lemin, int *parent, int final)
{
    printf("\e[92mget_shortpaths\e[0m\n");
    t_node  **shortpaths;
    t_node  *tmp;
    int     i;

    ////////////////////
    // printf("\e[93m\n");
    // print_paths_2(lemin->shortpath);
    // printf("\e[0m\n");
    ////////////////////
    i = lemin->count;
    shortpaths = lemin->shortpath;
    if (!lemin->links->visited[final])
        return ;
    if (!get_spurpaths(lemin, shortpaths[i], parent))
        return ;
    tmp = get_shortspurpath(lemin->spurpath, shortpaths[i]);
    if (tmp != NULL)
    {
        shortpaths[i + 1] = tmp;
        rebuildgraph(lemin, shortpaths[i + 1], SET);
        lemin->count++;
    }
    get_shortpaths(lemin, parent, final);

}

void        get_paths(t_lemin* lemin)
{
    printf("\e[92mget_paths\e[0m\n");
    int parent[lemin->rooms->total];
    int start;
    int final;
    int i;

    i = 0;
    start = lemin->rooms->start->id;
    final = lemin->rooms->end->id;
    lemin->shortpath = creat_paths(/* lemin->rooms->total */ 1000);
    lemin->spurpath = creat_paths(/* lemin->rooms->total */ 2000);
    search_path(lemin, creat_queue(), parent, start);
    add_path(lemin, lemin->shortpath, parent);
    if (lemin->links->visited[final])
        get_shortpaths(lemin, parent, final);
}
