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

// static int  is_duplicate(int src, t_path *dst)
// {
//     // printf("\e[93mis_duplicate\e[0m : ");
//     int i;

//     i = -1;
//     if (dst)
//     {
//         while (++i < dst->len)
//             if (dst->path[i] == src)
//                 return (1);
//     }
//     return (0);
// }

// static int  get_duplicate(t_path *src, t_path **all)
// {
//     // printf("\e[91mget_duplicate\e[0m\n");
//     int dup;
//     int i;
//     int j;

//     i = -1;
//     dup = 0;
//     while (++i < src->len - 1)
//     {
//         j = -1;
//         while (all[++j])
//         {
//             if (all[j] != src)
//                 if (is_duplicate(src->path[i], all[j]))
//                     dup++;
//         }
//     }
//     return (dup);
// }

// static void duplicate_paths(t_path **paths)
// {
//     // printf("\e[92mduplicate_paths\e[0m\n");
//     int j;

//     j = -1;
//     while (paths[++j])
//     {
//         paths[j]->dupl = get_duplicate(paths[j], paths);
//     }
// }

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
    // duplicate_paths(lemin.unique);
    lemin_play(&lemin);
    // printf("-------------unique-flow-------------\n");
    // int i = -1;
    // while (lemin.unique[++i])
    //     print_paths(lemin.unique[i], &lemin);
    return (0);
}
