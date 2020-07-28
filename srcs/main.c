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

void print_paths(t_path *paths, t_lemin *lemin)
{
    int i;

    i = -1;
    printf("\e[91mPath[%d]:", paths->len);
    while (++i < paths->len)
        printf(" %s", lemin->rooms->hroom[paths->path[i]]->name);
    printf("\e[0m\n");
}

void print_paths_2(t_lemin *lemin)
{
    t_node  **rooms;
    int     *tmp;
    int     i;
    int     j;

    rooms = lemin->rooms->hroom;
    tmp = lemin->primpath->path;
    // i = -1;
    // printf("\e[92mPrimepath[0][%d]:", lemin->primpath->len);
    // while (++i < lemin->primpath->len)
    //     printf(" %s", rooms[tmp[i]]->name);
    // printf("\e[0m\n");
    i = -1;
    while (lemin->shortpaths[++i])
    {
        j = -1;
        tmp = lemin->shortpaths[i]->path;
        printf("\e[93mShortpath[%d][%d]:", i, lemin->shortpaths[i]->len);
        while (++j < lemin->shortpaths[i]->len)
            printf(" %s", rooms[tmp[j]]->name);
        printf("\e[0m\n");
    }
    i = -1;
    while (lemin->spurpaths[++i])
    {
        j = -1;
        tmp = lemin->spurpaths[i]->path;
        printf("\e[91mSpurpaths[%d][%d]:", i, lemin->spurpaths[i]->len);
        while (++j < lemin->spurpaths[i]->len)
            printf(" %s", rooms[tmp[j]]->name);
        printf("\e[0m\n");
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
    // printf("---------------------\n");
    // print_paths_2(&lemin);
    // int i = -1;
    // while (lemin.shortpath[++i])
    //     ;
    // lemin.count = i;
    // lem_play(&lemin);
    return (0);
}
