#include "../includes/lemin.h"

void    lem_play(t_lemin *lemin)
{
    // printf("lem_play\n");
    t_node *ant[lemin->ants];
    int     count;
    int i;
    int k;

    i = -1;
    while (++i < lemin->ants)
        ant[i] = NULL;
    count = 0;
    while (count != lemin->ants)
    {
        // system("sleep 0.5");
        // printf("\e[93mlemin->ants = %d\e[0m\n", lemin->ants);
        i = 0;
        while (i < lemin->ants)
        {
            // printf("i = %d\n", i);
            // system("sleep 0.5");
            if (!ant[i])
            {
                // printf("ant[%d] = %s\n", i, ant[i]);
                // system("sleep 0.5");
                k = 0;
                while (lemin->paths[k])
                {
                    // printf("lemin->paths[%d]->name = %s\n", k, lemin->paths[k]->name);
                    // system("sleep 0.5");
                    if (!lemin->paths[k]->next->ant)
                    {
                        ant[i] = lemin->paths[k];
                        // printf("ant[%d]->name = %s\n", i, ant[i]->name);
                        // system("sleep 0.5");
                        break ;
                    }
                    k++;
                }
            }
            if (ant[i] && ant[i]->next)
            {
                if (ant[i]->next->id == lemin->rooms->end->id)
                {
                    ant[i]->ant--;
                    ant[i] = ant[i]->next;
                    ant[i]->ant++;
                    count++;
                    printf("L%d-%s ", i + 1, ant[i]->name);
                }
                else if (ant[i]->next->ant == 0)
                {
                    ant[i]->ant = 0;
                    ant[i] = ant[i]->next;
                    ant[i]->ant = 1;
                    printf("L%d-%s ", i + 1, ant[i]->name);
                }
            }
            i++;
        }
        printf("\n");
    }
}