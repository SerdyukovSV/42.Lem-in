#include "../includes/lemin.h"

void    lm_strdel(char **str)
{
    while (*str != NULL)
    {
        ft_strdel(&(*str));
        str += 1;
    }
}

void    lemin_init(t_lemin *lemin, char *str[])
{
    g_id = 0;
    lemin->ants = get_ants(str[0]);
    lemin->rooms = get_rooms(&str);
    lemin->links = get_links(lemin->rooms, str);
}

// int i = -1;
//     while (++i < lemin->rooms->total)
//         printf("%s %d %d\n", lemin->rooms->hroom[i]->name, lemin->rooms->hroom[i]->x, lemin->rooms->hroom[i]->y);

// int i = -1;
//     while (++i < lemin->rooms->total)
//     {
//         printf("%s", lemin->rooms->hroom[i]->name);
//         while (lemin->links->adjace[i])
//         {
//             printf("->%s", lemin->links->adjace[i]->name);
//             lemin->links->adjace[i] = lemin->links->adjace[i]->next;
//         }
//         printf("\n");
//     }