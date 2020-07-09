#include "../includes/lemin.h"

void    ft_error(int errcode)
{
    static char *err[] = {
        [ERR] = "Error",
        [NOARG] = "Missing arg",
        [INVDLINK] = "Invalid link",
        [INVDCOMM] = "Invalid command",
        [INVDROOM] = "Invalid room",
        [NOPATH] = "No paths"
    };
    if (errcode >= 0)
        printf("%s%s\n", !errcode ? "" : "Error: ", err[errcode]);
    else
        perror(err[errcode]);
    exit(EXIT_FAILURE);
}

int main(int ac, char **av)
{
    t_lemin lemin;
    char    **str;
    int     fd;

    if (ac < 2)
        ft_error(NOARG);
    str = lemin_read(av);
    if (lemin_validate(str))
    {
        lm_strdel(str);
        ft_error(ERR);
    }
    lemin_init(&lemin, &*str);
    lemin.parent = creat_paths(lemin.rooms->total);
    bfs(&lemin, lemin.links, lemin.rooms->start->id);
    // lemin_get_paths(lemin, lemin->rooms->end->id);

    return (0);
}