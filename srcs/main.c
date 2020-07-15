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
    // lemin.paths = new_paths(&lemin, lemin.paths, 0);
    int i = -1;
    t_node *tmp;
    while (lemin.paths[++i] && i < 4)
    {
        tmp = lemin.paths[i];
        while (tmp)
        {
            printf("Path[%d] | len[%d] = ", i, path_len(lemin.paths[i]));
            while (tmp)
            {
                printf("\e[93m->%d", tmp->id);
                tmp = tmp->next;
            }
            printf("\e[0m\n");
        }
    }
    lem_play(&lemin);
    return (0);
}
