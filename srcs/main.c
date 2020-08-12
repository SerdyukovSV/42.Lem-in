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

void print_paths_all(t_path **paths, t_lemin *lemin)
{
    int i;
    int j;

    i = -1;
    while (paths[++i])
    {
        j = -1;
        printf("\e[92mPath[%d][%d]:", paths[i]->len, paths[i]->flow);
        while (++j < paths[i]->len)
            printf(" %s", lemin->rooms->hroom[paths[i]->path[j]]->name);
        printf("\e[0m\n");
    }
}

void print_paths(t_path *paths, t_lemin *lemin)
{
    int i;

    i = -1;
    if (paths)
    {
        printf("\e[91mPath[%d][%d]:", paths->len, paths->flow);
        while (++i < paths->len)
            printf(" %s", lemin->rooms->hroom[paths->path[i]]->name);
    }
    printf("\e[0m\n");
}

void print_paths_2(t_lemin *lemin)
{
    t_node  **rooms;
    t_path  *root;
    t_path  **spur;
    int     i;
    int     j;

    i = -1;
    rooms = lemin->rooms->hroom;
    while (lemin->shortpaths[++i])
    {
        spur = lemin->shortpaths[i]->spurpaths;
        while (*spur)
        {
            j = -1;
            root = (*spur);
            printf("\e[93mSpur[%d][%d]:", root->len, root->flow);
            while (++j < root->len)
                printf(" %s", rooms[root->path[j]]->name);
            printf("\e[0m\n");
            spur += 1;
        }
        printf("\n");
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
    lemin.unique = malloc(sizeof(t_path *) * 100);
    ft_memset(lemin.unique, 0, sizeof(t_path *) * 100);
    // print_paths_2(&lemin);
    choice_paths(&lemin);
    printf("-------------unique-flow-------------\n");
    int i = -1;
    while (lemin.unique[++i])
        print_paths(lemin.unique[i], &lemin);
    lemin.size = lemin.ants;
    lemin_play(&lemin);
    return (0);
}
