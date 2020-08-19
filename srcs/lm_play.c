#include "../includes/lemin.h"

static void     rebuildlink(t_lemin *lemin)
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
                    // tmp->path = 2;
                    break ;
                }
                tmp = tmp->next;
            }
            tmp = lemin->links->adjace[tmp->id];
        }
    }
}

static t_node   *get_next(t_lemin *lemin, t_node *ants)
{
    // printf("\e[92mget_next\n\e[0m");
    t_node  *tmp;

    if (ants->id == lemin->final)
        return (ants);
    tmp = lemin->links->adjace[ants->id];
    while (tmp)
    {
        // if (tmp->path == 2)
        // {
        //     ants = tmp;
        //     ants->ant = 1;
        //     break ;
        // }
        tmp = tmp->next;
    }
    return (ants);
}

static void     get_start(t_lemin *lemin, t_node **ants)
{
    // printf("\e[92mget_start\n\e[0m");
    t_node  *start;
    int     i;
    int     j;

    i = -1;
    while (lemin->unique[++i])
    {
        // printf("unique[%d]->flow = %d\n", i, lemin->unique[i]->flow);
        if (lemin->unique[i]->flow > 0)
        {
            j = -1;
            start = lemin->links->adjace[lemin->start];
            while (lemin->unique[i]->path[0] != start->id)
                start = start->next;
            while (++j < lemin->ants)
            {
                // printf("j = %d\n", j);
                if (!ants[j] && !start->ant)
                {
                    ants[j] = start;
                    ants[j]->ant = 1;
                    lemin->unique[i]->flow--;
                    break ;
                }
            }
        }
    }
}

void            lemin_play(t_lemin *lemin)
{
    t_node  *ants[lemin->ants + 1];
    int     fin[lemin->ants];
    int     i;
    int line; //del

    line = 0;
    rebuildlink(lemin);
    set_flow(lemin, get_flow(lemin->unique, lemin->ants));
    ft_bzero(fin, sizeof(int) * lemin->ants);
    ft_bzero(ants, sizeof(t_node *) * (lemin->ants + 1));
    while (lemin->size)
    {
        i = -1;
        get_start(lemin, ants);
        while (ants[++i])
        {
            if (ants[i]->ant && !fin[i])
            {
                printf("L%d-%s ", i + 1, ants[i]->name);
                ants[i]->ant = 0;
                ants[i]->id == lemin->final ? (fin[i] = 1) : 0;
                ants[i]->id == lemin->final ? lemin->size-- : 0;
                ants[i] = get_next(lemin, ants[i]);
            }
        }
        line++;
        printf("\n");
    }
    printf("\e[92mline #%d\n\e[0m", line);
}
