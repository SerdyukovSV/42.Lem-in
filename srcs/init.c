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
    lemin->rooms = get_rooms(str);
    // get_links(fd, &line, lemin);

    // return (lemin);
}