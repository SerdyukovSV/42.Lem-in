#include "../includes/lemin.h"

int path_count(t_path **paths)
{
    // printf("path_count\n");
    int i;

    i = 0;
    while (paths[i])
        i++;
    return (i);
}

static void     search_path(t_lemin *lem, t_queue *queue, int *parent, int current)
{
    // printf("search_path\n");
    t_node      *tmp;

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

static void     spurpaths(t_lemin *lem, t_path *root, t_path **spur, int *par)
{
    // printf("spurpaths\n");
    t_path  *new;
    int     i;
    int     j;

    j = 0;
    lem->possible = 1;
    // while (lem->possible > 0)
    // {
        i = -1;
        while (++i < root->len && root->path[i + 1] != -1 && lem->possible > 0)
        {
            ft_bzero(lem->links->visited, sizeof(int) * lem->rooms->total);
            setvertex(lem, root->path[i], DEL);
            setlink_root(lem, &root->path[i], DEL);
            search_path(lem, creat_queue(), par, root->path[i]);
            if (lem->links->visited[lem->final])
            {
                new = pathjoin(root, newpath(par, lem->final), root->path[i]);
                if (!cmp_paths(spur, new))
                    if ((spur[j++] = new))
                        setlink_spur(lem, spur[j - 1], root->path[i], DEL);
            }
            lem->possible--;
        }
    // }
}

static t_path   *rootpath(t_lemin *lemin, t_node *start)
{
    // printf("rootpath\n");
    int parent[lemin->rooms->total];
    t_path *new;

    ft_bzero(lemin->links->visited, sizeof(int) * lemin->rooms->total);
    search_path(lemin, creat_queue(), parent, start->id);
    if (lemin->links->visited[lemin->final])
    {
        if ((new = newpath(parent, lemin->final)))
            return (new);
    }
    return (NULL);
}

static void     get_shortpaths(t_lemin *lemin, t_shortpath **shortpaths, int *par, t_node *start)
{
    // printf("get_shortpaths\n");
    t_path  *tmp;
    t_node  *end;
    int     i;
    int     j;
    int     b;

    i = 0;
    while (start)
    {
        // printf("\e[92mstart = %s\e[0m\n", start->name);
        // printf("i = %d\n", i);
        end = lemin->links->adjace[lemin->final];
        lemin->final = end->id;
        if (!(shortpaths[i] = (t_shortpath *)malloc(sizeof(t_shortpath)))) ft_error(ERR);
        if (!(shortpaths[i]->spurpaths = malloc(sizeof(t_path *) * 100))) ft_error(ERR);
        ft_memset(shortpaths[i]->spurpaths, 0, sizeof(t_path *) * 100);
        b = 0;
        while (end)
        {
            // printf("\e[93mend = %s\e[0m\n", end->name);
            if ((tmp = rootpath(lemin, start)) != NULL)
            {
                b = 1;
                // print_paths(tmp, lemin);
                // system("sleep 0.5");
                shortpaths[i]->rootpath = tmp;
                j = path_count(shortpaths[i]->spurpaths);
                shortpaths[i]->spurpaths[j] = shortpaths[i]->rootpath;
                // possible_paths(lemin, shortpaths[i]->rootpath);
                spurpaths(lemin, shortpaths[i]->rootpath, shortpaths[i]->spurpaths + j, par);
                rebuildgraph(lemin, shortpaths[i], SET);
            }
            if ((end = end->next))
                lemin->final = end->id;
        }
        if (b == 1)
            i++;
        else
            shortpaths[i] = NULL;
        start = start->next;
        lemin->final = lemin->rooms->end->id;
    }
}

void            get_paths(t_lemin* lemin)
{
    int     parent[lemin->rooms->total];
    t_node  *start;

    start = lemin->links->adjace[lemin->start];
    setvertex(lemin, lemin->start, DEL);
    setvertex(lemin, lemin->final, DEL);
    if (!(lemin->shortpaths = malloc(sizeof(t_shortpath *) * lemin->size * 2)))
        ft_error(ERR);
    ft_memset(lemin->shortpaths, 0, sizeof(t_shortpath *) * (lemin->size * 2));
    get_shortpaths(lemin, lemin->shortpaths, parent, start);
    add_end_paths(lemin);
    sort_spurpaths(lemin->shortpaths);
    sort_rootpaths(lemin->shortpaths);
}
