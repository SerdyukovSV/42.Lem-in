#include "../includes/lemin.h"

void    set_flow(t_lemin *lemin, int flow)
{
    int flow_ant;
    int ants;
    int i;

    i = 0;
    flow_ant = 0;
    ants = lemin->ants;
    while (lemin->paths[i])
    {
        lemin->paths[i]->flow = 0;
        flow_ant = flow - lemin->paths[i]->len + 2;
        if (flow_ant < ants)
            lemin->paths[i]->flow = flow_ant;
        else
            lemin->paths[i]->flow = ants;
        ants -= lemin->paths[i]->flow;
        i++;
    }
}

int     get_flow(t_path **paths, int ants)
{
    int ln;
    float flow1;
    float flow2;
    int count;

    ln = 0;
    count = 0;
    flow1 = INT32_MAX;
    flow2 = INT32_MAX;
    while (paths[count])
    {
        ln += paths[count++]->len - 1;
        flow1 = ((float)ln + ants - 1) / count;
        if (flow1 < flow2)
            flow2 = flow1;
        else
            break ;
    }
    return (flow2);
}

void    sort_paths(t_path **paths)
{
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

void    set_capacity(t_lemin *lemin, t_node *src, t_node *dst, int set)
{
    // printf("set_capacity_edge\n");
    t_node *tmp;

    tmp = lemin->links->adjace[src->id];
    while (tmp)
    {
        if (tmp->id == dst->id)
        {
            tmp->capacity += set;
            break ;
        }
        tmp = tmp->next;
    }
}

void    set_attributes(t_lemin *lemin, t_path **paths)
{
    // printf("set_attributes\n");
    t_node  **node;
    int i;
    int j;

    i = -1;
    node = lemin->node;
    while (lemin->node[++i])
    {
        node[i]->in_path = 0;
        node[i]->previous = -1;
    }
    i = -1;
    while (paths[++i])
    {
        j = 0;
        while (paths[i]->node[j])
        {
            node[paths[i]->node[j++]->id]->in_path = 1;
            if (paths[i]->node[j])
                node[paths[i]->node[j]->id]->previous = paths[i]->node[j - 1]->id;
        }
    }
}

void    rebuildgraph(t_lemin *lemin, t_path *path, int set)
{
    // printf("rebuildgraph\n");
    t_node  **node;
    int     ln;
    int     i;

    i = 0;
    ln = path->len;
    node = path->node;
    while (ln--)
    {
        if (set == SET && (ln - 1) >= 0)
        {
            set_capacity(lemin, node[ln], node[ln - 1], DECREASE);
            set_capacity(lemin, node[ln - 1], node[ln], INCREASE);

        }
        else if (set == DEL && (ln - 1) >= 0)
        {
            set_capacity(lemin, node[ln], node[ln - 1], INCREASE);
            set_capacity(lemin, node[ln - 1], node[ln], DECREASE);
        }
    }
}