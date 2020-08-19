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

void print_paths_all(t_path **paths)
{
    int i;
    int j;

    i = -1;
    while (paths[++i])
    {
        j = -1;
        printf("\e[92mPath[%d][%d]:", paths[i]->len, paths[i]->flow);
        while (++j < paths[i]->len)
            printf(" %s", paths[i]->node[j]->name);
        printf("\e[0m\n");
    }
}

void print_path(t_path *path)
{
    int i;

    i = -1;
    if (path)
    {
        printf("\e[91mPath[%d][%d]:", path->len, path->flow);
        while (++i < path->len)
            printf(" %s", path->node[i]->name);
    }
    printf("\e[0m\n");
}

static int  is_duplicate(t_node *src, t_path *dst)
{
    // printf("\e[93mis_duplicate\e[0m : ");
    int i;

    i = -1;
    if (dst)
    {
        while (++i < dst->len)
            if (dst->node[i]->id == src->id)
                return (1);
    }
    return (0);
}

static int  get_duplicate(t_path *src, t_path **all)
{
    // printf("\e[91mget_duplicate\e[0m\n");
    int dup;
    int i;
    int j;

    i = -1;
    dup = 0;
    while (++i < src->len - 1)
    {
        j = -1;
        while (all[++j])
        {
            if (all[j] != src)
                if (is_duplicate(src->node[i], all[j]))
                    dup++;
        }
    }
    return (dup);
}

static void duplicate_paths(t_path **paths)
{
    // printf("\e[92mduplicate_paths\e[0m\n");
    int i;

    i = -1;
    while (paths[++i])
    {
        paths[i]->flow = get_duplicate(paths[i], paths);
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
    get_paths(&lemin);
    // print_paths_2(&lemin);
    // choice_paths(&lemin);
    duplicate_paths(lemin.paths);
    printf("-------------paths-------------\n");
    printf("Line #%d\n", get_flow(lemin.paths, lemin.ants));
    int i = -1;
    while (lemin.paths[++i])
        print_path(lemin.paths[i]);
    // lemin.size = lemin.ants;
    // lemin_play(&lemin);
    return (0);
}
