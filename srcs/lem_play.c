#include "../includes/lemin.h"

static void     set_flow(t_lemin *lemin, int flow)
{
    int flow_ant;
    int i;

    i = 0;
    flow_ant = 0;
    while (lemin->unique[i])
    {
        lemin->unique[i]->flow = 0;
        flow_ant = flow - lemin->unique[i]->len + 1;
        if (flow_ant < lemin->ants)
            lemin->unique[i]->flow = flow_ant;
        else
            lemin->unique[i]->flow = lemin->ants;
        lemin->ants -= lemin->unique[i]->flow;
        i++;
    }
}

static int      get_flow(t_path **paths, int ants)
{
    int ln;
    int flow1;
    int flow2;
    int count;

    ln = 0;
    count = 0;
    flow1 = INT32_MAX;
    flow2 = INT32_MAX;
    while (paths[count])
    {
        ln += paths[count++]->len;
        flow1 = (ln / count) + (ants / count);
        if (flow1 < flow2)
            flow2 = flow1;
    }
    printf("\e[92mflow = %d\e[0m\n", flow2);
    return (flow2);
}

static void     rebuildgraph(t_lemin *lemin)
{
    t_node  *tmp;
    int     i;
    int     j;

    i = -1;
    while (lemin->unique[++i])
    {
        j = -1;
        tmp = lemin->links->adjace[lemin->start];
        while (++j < lemin->unique[i]->len)
        {
            while (tmp)
            {
                if (tmp->id == lemin->unique[i]->path[j])
                {
                    tmp->path = 2;
                    break ;
                }
                tmp = tmp->next;
            }
            tmp = lemin->links->adjace[tmp->id];
        }
    }
}

static t_node   *start_ant(t_lemin *lemin, t_node **ants)
{
    int start;
    int i;
    int j;

    i = -1;
    while (lemin->unique[++i])
    {
        if (lemin->unique[i]->flow)
        {
            j = -1;
            start = lemin->unique[i]->path[0];
            while (++j < lemin->ants)
            {
                if (!ants[j] && !lemin->links->adjace[start]->ant)
                {
                    ants[j] = lemin->links->adjace[start];
                    ants[j]->ant = 1;
                    break ;
                }
            }
        }
    }
}

void            lemin_play(t_lemin *lemin)
{
    t_node  *ants[lemin->ants];
    t_node  *tmp;
    int     i;

    rebuildgraph(lemin);
    set_flow(lemin, get_flow(lemin->unique, lemin->ants));
    while (lemin->ants)
    {
        i = 0;
        start_ant(lemin, ants);
        while (ants[i])
        {
            if (ants[i]->ant)
            {
                printf("L%d-%d ", i + 1, ants[i]->name);
                ants[i]->ant = 0;
                tmp = lemin->links->adjace[ants[i]->id];
                while (tmp)
                {
                    if (tmp->path == 2)
                    {
                        ants[i] = tmp;
                        ants[i]->ant = 1;
                    }
                }
            }
        }
    // while (start)
    // {
    //     if (start->path == 2)
    //     {
    //         printf("\e[92mPath:");
    //         printf("\e[93m %s", start->name);
    //         tmp = links[start->id];
    //         while (tmp)
    //         {
    //             if (tmp->path == 2)
    //             {
    //                 printf(" %s", tmp->name);
    //                 tmp = links[tmp->id];
    //                 continue ;
    //             }
    //             tmp = tmp->next;
    //         }
    //         printf("\e[0m\n");
    //     }
    //     start = start->next;
    // }
    }
}