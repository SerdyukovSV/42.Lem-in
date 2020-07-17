#include "../includes/lemin.h"

static int pathlen(t_node *path)
{
    size_t i;

    i = 0;
    while (path)
    {
        i++;
        path = path->next;
    }
    i -= i > 0 ? 1 : 0;
    return (i);
    
}

static void set_anttopath(t_lemin *lem, int *p_ant)
{
    // printf("\e[91mset_anttopath\e[0m\n");
    int step[lem->count];
    int i;
    int j;

    i = 0;
    j = 1;
    ft_bzero(step, sizeof(step));
    p_ant[i] = lem->ants;
    step[i] = pathlen(lem->paths[i]) + p_ant[i] - (p_ant[i] ? 1 : 0);
    while (j < lem->count)
    {
        step[j] = pathlen(lem->paths[j]) + p_ant[j] - (p_ant[j] ? 1 : 0);
        if (step[i] > step[j])
        {
            p_ant[j] += 1;
            step[j] = pathlen(lem->paths[j]) + p_ant[j] - (p_ant[j] ? 1 : 0);
            p_ant[i]--;
            step[i]--;
            i = 0;
            j = 1;
        }
        else
        {
            i++;
            j++;
        }
    }
    i = -1;
    while (++i < lem->count && p_ant[i])
        printf("\e[92mp_ant[%d] = %d\n", i, p_ant[i]);
    lem->size = i;
}

void    lem_play(t_lemin *lemin)
{
    // printf("\e[91mlem_play\e[0m\n");
    t_node *ant[lemin->ants];
    int     count;
    int     line;
    int     path_ant[lemin->count];
    int i;
    int k;

    i = -1;
    while (++i < lemin->ants)
        ant[i] = NULL;
    count = 0;
    line = 0;
    ft_bzero(path_ant, sizeof(path_ant));
    set_anttopath(lemin, path_ant);
    while (count != lemin->ants)
    {
        // printf("\e[93mstep_2\e[0m\n");
        // printf("lemin->size = %d\n", lemin->size);
        // system("sleep 0.05");
        i = -1;
        while (++i < lemin->ants)
        {
            k = -1;
            while (!ant[i] && ++k < lemin->size)
            {
                if (path_ant[k] && !lemin->paths[k]->next->ant)
                {
                    ant[i] = lemin->paths[k];
                    path_ant[k]--;
                }
            }
            if (ant[i])
            {
                if (ant[i]->next && ant[i]->next->id == lemin->rooms->end->id)
                {
                    ant[i]->ant--;
                    ant[i] = ant[i]->next;
                    ant[i]->ant++;
                    count++;
                    printf("\e[92mL%d-%d\e[0m ", i + 1, ant[i]->id);
                }
                else if (ant[i]->next && ant[i]->next->ant == 0)
                {
                    ant[i]->ant = 0;
                    ant[i] = ant[i]->next;
                    ant[i]->ant = 1;
                    printf("L%d-%d ", i + 1, ant[i]->id);
                }
            }
        }
        line++;
        printf("\n");
    }
    printf("\e[92mlines #%d\e[0m\n", line);
}


// static int set_anttopath(t_lemin *lem, int *p_ant)
// {
//     int max;
//     int i;
//     int j;

//     i = 0;
//     max = 0;
//     while (i < lem->count && max < lem->ants)
//         max += pathlen(lem->paths[i++]) - 1;
//     j = -1;
//     max = 0;
//     while (++j < i)
//     {
//         p_ant[j] = pathlen(lem->paths[i - 1]) - pathlen(lem->paths[j]) + 1;
//         max += p_ant[j];
//     }
//     j = 0;
//     while (lem->ants > max)
//     {
//         (j < i) ? p_ant[j]++ : 0;
//         (j < i) ? max++ : 0;
//         (j < i) ? j++ : (j = 0);
//     }
//     return (i);
// }