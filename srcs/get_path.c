#include "../includes/lemin.h"

static int  adj_length(t_links *adj, int room)
{
    t_node  *tmp;
    int     len;

    len = 0;
    tmp = adj->adjace[room];
    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }
    return (len);
}

void        push_path(t_path **path, int room)
{
    t_path *tmp;

    if (!(tmp = malloc(sizeof(t_path))))
        ft_error(ERR);
    tmp->room = room;
    tmp->next = *path;
    *path = tmp;
}

int         isduplicate(t_path **path, int val, int len)
{
    t_path  *tmp;
    int     i;

    i = 0;
    while (i < len)
    {
        tmp = path[i];
        while (tmp)
        {
            if (tmp->room == val)
                return (1);
            tmp = tmp->next;
        }
    }
    return (0);
}

t_path      **creat_paths(int len)
{
    t_path  **path;
    int     i;

    if (!(path = malloc(sizeof(t_path *) * len)))
        ft_error(ERR);
    i = -1;
    while (++i < len)
        path[i] = NULL;
    return (path);
}

void        lemin_get_paths(t_lemin *lem, int final)
{
    t_path      **tmp;
    int         len;
    int         p;
    int         i;

    len = adj_length(lem->links, final);
    lem->paths = creat_paths(len);
    if (!lem->links->visited[final])
        ft_error(NOPATH);
    i = 0;
    tmp = lem->parent;
    while (i < len)
    {
        push_path(&lem->paths[i], final);
        p = final;
        while (tmp[p] && tmp[p]->room != -1)
        {
            push_path(&lem->paths[i], tmp[p]->room);
            // if (tmp[p]->next)
                tmp[p] = tmp[p]->next;
            p = lem->paths[i]->room;
        }
        i++;
    }
    // i = 0;
    // while (i < len)
    // {
    //     printf("Path[%d] : %s", i, lem->adjrms->rooms[lem->paths[i]->room]->name);
    //     lem->paths[i] = lem->paths[i]->next;
    //     while (lem->paths[i])
    //     {
    //         printf("->%s", lem->adjrms->rooms[lem->paths[i]->room]->name);
    //         lem->paths[i] = lem->paths[i]->next;
    //     }
    //     i++;
    //     printf("\n");
    // }
}