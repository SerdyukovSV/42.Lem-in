#include "../includes/lemin.h"

static int path_len(t_node *path)
{
    size_t i;

    i = 0;
    while (path)
    {
        i++;
        path = path->next;
    }
    return (i);
    
}

void    lem_play(t_lemin *lemin)
{
    t_node *ant[lemin->ants];
    int     count;
    int     line;
    int i;
    int k;

    i = -1;
    while (++i < lemin->ants)
        ant[i] = NULL;
    count = 0;
    line = 0;
    while (count != lemin->ants)
    {
        i = -1;
        while (++i < lemin->ants)
        {
            if (!ant[i])
            {
                k = 0;
                while (lemin->paths[k] && k < 1)
                {
                    // if (path_len(lemin->paths[k]) <= (lemin->ants - count))
                    // {
                        if (!lemin->paths[k]->next->ant)
                        {
                            ant[i] = lemin->paths[k];
                            break ;
                        }
                        k++;
                    // }
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
        }
        line++;
        printf("\n");
    }
    printf("\e[92mlines = %d\e[0m\n", line);
}