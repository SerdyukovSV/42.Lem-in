#include "../includes/lemin.h"

void    lem_play(t_lemin *lemin)
{
    printf("lem_play\n");
    t_node *ant[lemin->ants];
    int i;
    int k;

    i = -1;
    while (++i < lemin->ants)
        ant[i] = NULL;
    while (lemin->ants)
    {
        // printf("step_1\n");
        i = 0;
        while (i < lemin->ants)
        {
            if (!ant[i])
            {
                k = 0;
                // printf("lemin->paths[%d]->next->ant = %d\n", k, lemin->paths[k]->next->ant);
                while (lemin->paths[k])
                {
                    // printf("lemin->paths[%d]->next->ant = %d\n", k, lemin->paths[k]->next->ant);
                    if (!lemin->paths[k]->next->ant)
                    {
                        ant[i] = lemin->paths[k]->next;
                        break ;
                    }
                    k++;
                }
            }
            if ((ant[i]->next && !ant[i]->next->ant) || ant[i]->next->ant > 1)
            {
                // printf("step_6\n");
                ant[i]->ant = 0;
                ant[i] = ant[i]->next;
                if (ant[i]->id == lemin->rooms->end->id)
                {
                    ant[i]->ant++;
                    lemin->ants--;
                }
                else
                    ant[i]->ant = 1;
                printf("L%d - %s; ", i + 1, ant[i]->name);
            }
            i++;
        }
        printf("\n");
    }
}