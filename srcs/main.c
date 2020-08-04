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
    printf("\e[91mPath[%d][%d]:", paths->len, paths->dupl);
    while (++i < paths->len)
        printf(" %s", lemin->rooms->hroom[paths->path[i]]->name);
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
        // j = -1;
        // root = lemin->shortpaths[i]->rootpath;
        // printf("\e[92mRoot[%d][%d]:", root->len, root->dupl);
        // while (++j < root->len)
        //     printf(" %s", rooms[root->path[j]]->name);
        // printf("\e[0m\n");
        spur = lemin->shortpaths[i]->spurpaths;
        while (*spur)
        {
            j = -1;
            root = (*spur);
            printf("\e[93mSpur[%d][%d]:", root->len, root->dupl);
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
    // get_paths(&lemin, lemin.links, lemin.rooms->start->id);
    get_paths(&lemin);
    // duplicate_paths(lemin.shortpaths);
    // print_paths_2(&lemin);
    choice_paths(&lemin);
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
