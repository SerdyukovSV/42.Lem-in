#include "../includes/lemin.h"

void    ft_error(int errcode)
{
    static char *err[] = {
        [ERR] = "ERROR",
        [NOARG] = "missing argument",
        [INVDLINK] = "Invalid link",
        [INVDCOMM] = "Invalid command",
        [INVDROOM] = "Invalid room",
        [NOPATH] = "No paths"
    };
    if (errcode >= 0)
        printf("%s: %s\n", !errcode ? "" : err[0], err[errcode]);
    else
        perror(err[errcode]);
    exit(EXIT_FAILURE);
}

int main(int ac, char **av)
{
    t_lemin lemin;
    char    **str;

    if (ac < 2)
        ft_error(NOARG);
    str = lemin_read(av);
    if (lemin_validate(str))
    {
        lm_strdel(str);
        ft_error(ERR);
    }
    lemin_init(&lemin, &*str);
    get_paths(&lemin, lemin.links, lemin.rooms->start->id);
    lemin.paths = new_paths(&lemin, lemin.paths, 0);
    // int i = -1;
    // t_node **tmp;
    // tmp = lemin.paths;
    // while (tmp[++i])
    // {
    //     printf("Path[%d] = ", i);
    //     while (tmp[i])
    //     {
    //         printf("\e[93m->%s", tmp[i]->name);
    //         tmp[i] = tmp[i]->next;
    //     }
    //     printf("\e[0m\n");
    // }
    lem_play(&lemin);
    return (0);
}


// int i = -1;
//     while (lemin.paths[++i])
//     {
//         printf("Path[%d] = ", i);
//         while (lemin.paths[i])
//         {
//             printf("\e[93m->%d", lemin.paths[i]->id);
//             lemin.paths[i] = lemin.paths[i]->next;
//         }
//         printf("\e[0m\n");
//     }