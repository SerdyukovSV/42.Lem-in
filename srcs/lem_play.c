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

static int solve_path(int len1, int len2, int ant)
{
    // printf("\e[91msolve_path\e[0m\n");
    // printf("\e[91mlen1 = %d len2 = %d ant = %d\e[0m\n", len1, len2, ant);
    // printf("%d < %d\n", len2, (len1 + (ant - 1)));

    return (len1 <= (len2 + (ant - 1)));
    // return ((len1 + len2) <= (len2 + (ant - 1)));
}

void    lem_play(t_lemin *lemin)
{
    t_node *ant[lemin->ants];
    int     count;
    int     count2;
    int     line;
    int i;
    int k;

    i = -1;
    while (++i < lemin->ants)
        ant[i] = NULL;
    count = 0;
    count2 = 0;
    line = 0;
    while (count != lemin->ants)
    {
        i = -1;
        while (++i < lemin->ants)
        {
            if (!ant[i])
            {
                k = 0;
                while (lemin->paths[k] && /* !ant[i] */ k < 2)
                {
                    if (!k && !lemin->paths[k]->next->ant)
                    {
                        ant[i] = lemin->paths[k];
                        count2++;
                        break ;
                    }
                    else if (k > 0 && solve_path(path_len(lemin->paths[k]) - 1, path_len(lemin->paths[0]) - 1, lemin->ants - count2))
                    {
                        if (!lemin->paths[k]->next->ant)
                        {
                            ant[i] = lemin->paths[k];
                            count2++;
                            break ;
                        }
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
                    printf("L%d-%d ", i + 1, ant[i]->id);
                }
                else if (ant[i]->next->ant == 0)
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
    printf("\e[92mlines = %d\e[0m\n", line);
}