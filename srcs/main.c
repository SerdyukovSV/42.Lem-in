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

int path_len(t_node *path)
{
    size_t i;

    i = 0;
    while (path)
    {
        i++;
        path = path->next;
    }
    // i -= i > 0 ? 1 : 0;
    return (i);
    
}

int path_len_2(t_node *path)
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

void print_paths(t_node *paths, int i)
{
    while (paths)
    {
        printf("Path[%d][%d] = ", i, path_len(paths));
        while (paths)
        {
            printf("->%s", paths->name);
            paths = paths->next;
        }
        printf("\n");
    }
    printf("\e[0m");
}

void print_paths_2(t_node **paths)
{
    int i = -1;
    t_node *tmp;

    while (paths[++i])
    {
        tmp = paths[i];
        while (tmp)
        {
            printf("\e[93mPath[%d][%d] = ", i, path_len_2(paths[i]));
            while (tmp)
            {
                printf("->%s", tmp->name);
                tmp = tmp->next;
            }
            printf("\n\e[0m");
        }
    }
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
    // get_paths(&lemin, lemin.links, lemin.rooms->start->id);
    get_paths(&lemin);
    // lemin.paths = new_paths(&lemin, lemin.paths);
    // printf("+++++++++++++++++++++\n");
    print_paths_2(lemin.paths);
    printf("---------------------\n");
    print_paths_2(lemin.spurpath);
    int i = -1;
    while (lemin.paths[++i])
        ;
    // lemin.count = i;
    // lem_play(&lemin);
    return (0);
}
