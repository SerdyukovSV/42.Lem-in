#include "../includes/lemin.h"

static t_node   **create_node(t_rooms *room)
{
    t_node  *head;
    t_node  **node;

    if (!room)
        return (NULL);
    head = room->head;
    if (!(node = malloc(sizeof(t_node *) * room->total + 1)))
        return (NULL);
    while (head)
    {
        node[head->id] = head;
        head = head->next;
    }
    node[room->total] = NULL;
    return (node);
}

static int      get_countpath(t_lemin *lemin)
{
    t_node  *tmp;
    int     i;

    i = 0;
    tmp = lemin->links->adjace[lemin->start];
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

void            init_attributes(t_lemin *lemin)
{
    lemin->ants = 0;
    lemin->size = 0;
    lemin->count = 0;
    lemin->final = 0;
    lemin->start = 0;
    lemin->str = NULL;
    lemin->node = NULL;
    lemin->rooms = NULL;
    lemin->links = NULL;
    lemin->paths = NULL;
    lemin->queue = NULL;
    lemin->parent = NULL;
}

void            lemin_init(t_lemin *lemin)
{
    char    **str;

    g_id = 0;
    str = lemin->str;
    lemin->ants = get_ants(str[0]);
    lemin->rooms = get_rooms(&str);
    lemin->node = create_node(lemin->rooms);
    if (!lemin->rooms || !lemin->node)
        ft_error(lemin, ERR);
    if ((lemin->links = get_links(lemin, str)) == NULL)
        ft_error(lemin, ERR);
    str = NULL;
    lemin->size = get_countpath(lemin);
    lemin->final = lemin->rooms->end->id;
    lemin->start = lemin->rooms->start->id;
}
