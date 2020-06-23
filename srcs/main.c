#include "../includes/lemin.h"

void    ft_error(char *str)
{
    if (str != NULL)
    {
        if (!ft_strcmp(str, NOARG))
            printf("Error: %s\n", str);
        else
            perror(str);
    }
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    int fd;
    t_lemin *lemin;

    if (argc < 2)
        ft_error(NOARG);
    if ((fd = open(argv[1], O_RDONLY)) == -1)
        ft_error(ERR);
    lemin = lemin_init(fd);
    lemin->parent = lemin_creat_paths(lemin->rooms->total);
    breadth_first_search(lemin, lemin->adjrms, lemin->rooms->start->id);
    lemin_get_paths(lemin, lemin->rooms->end->id);

    return (0);
}