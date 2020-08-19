#include "../includes/lemin.h"

void        lm_strdel(char **str)
{
    while (*str != NULL)
    {
        ft_strdel(&(*str));
        str += 1;
    }
}

static int  get_size_path(t_links *link, int start, int final)
{
    t_node  *tmp;
    int     i;
    int     k;

    i = 0;
    tmp = link->adjace[start];
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    k = 0;
    tmp = link->adjace[final];
    while (tmp)
    {
        tmp = tmp->next;
        k++;
    }
    // printf("start = %d | end = %d\n", i, k);
    return ((i > k) ? k : i);
}

void        lemin_init(t_lemin *lemin, char *str[])
{
    g_id = 0;
    lemin->count = 0;
    lemin->ants = get_ants(str[0]);
    lemin->rooms = get_rooms(&str);
    lemin->links = get_links(lemin->rooms, str);
    lemin->node = lemin->rooms->hroom;
    lemin->start = lemin->rooms->start->id;
    lemin->final = lemin->rooms->end->id;
    lemin->size = get_size_path(lemin->links, lemin->start, lemin->final);
}
