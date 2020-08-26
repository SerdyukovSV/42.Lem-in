#include "../includes/lemin.h"

void print_paths(t_path **paths)
{
    int i;
    int j;

    i = -1;
    while (paths[++i])
    {
        j = -1;
        // printf("\e[92mPath[%d][%d]:", paths[i]->len, paths[i]->flow);
        printf("Path[%d][%d]:", paths[i]->len, paths[i]->flow);
        while (++j < paths[i]->len)
            printf(" %s", paths[i]->node[j]->name);
        printf("\n");
    }
}

int     main(int ac, char **av)
{
    t_lemin lemin;
    int     ret;

    ret = 0;
    if (ac > 1)
    {
        ft_putendl("Usage:");
        ft_putstr(av[0]);
        ft_putendl(" < maps/file.map");
        return (0);
    }
    init_attributes(&lemin);
    if (!(lemin.str = lemin_read(&lemin)))
        ft_error(&lemin, ERR);
    lemin_init(&lemin);
    get_paths(&lemin);
    lemin.size = lemin.ants;
    lemin_play(&lemin);
    lemin_free(&lemin);
    return (EXIT_SUCCESS);
}
