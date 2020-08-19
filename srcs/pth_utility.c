#include "../includes/lemin.h"

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
        // printf("STEP_2\n");
        j = 0;
        while (paths[i]->node[j])
        {
            // printf("step_3\n");
            node[paths[i]->node[j++]->id]->in_path = 1;
            if (paths[i]->node[j])
                node[paths[i]->node[j]->id]->previous = paths[i]->node[j - 1]->id;
        }
    }
    // t_node *tmp;
    // tmp = lemin->links->adjace[lemin->start];
    // printf("\e[94mstart[%s]", lemin->rooms->start->name);
    // while (tmp)
    // {
    //     printf("->%s", tmp->name);
    //     tmp = tmp->next;
    // }
    // printf("\e[0m\n");
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
    // printf("ln = %d\n", ln);
    while (ln--)
    {
        // printf("in | SET = %d\n", set);
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
        // printf("out\n");
    }
}