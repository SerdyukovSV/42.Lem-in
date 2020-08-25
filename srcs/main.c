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

// int  is_duplicate(t_node *src, t_path *dst)
// {
//     // printf("\e[93mis_duplicate\e[0m : ");
//     int i;

//     i = -1;
//     if (dst)
//     {
//         while (++i < dst->len)
//             if (dst->node[i]->id == src->id)
//                 return (1);
//     }
//     return (0);
// }

// int  get_duplicate(t_path *src, t_path **all)
// {
//     // printf("\e[91mget_duplicate\e[0m\n");
//     int dup;
//     int i;
//     int j;

//     i = 0;
//     dup = 0;
//     while (++i < src->len - 1)
//     {
//         j = -1;
//         while (all[++j])
//         {
//             if (all[j] != src)
//                 if (is_duplicate(src->node[i], all[j]))
//                     dup++;
//         }
//     }
//     return (dup);
// }

// void duplicate_paths(t_path **paths)
// {
//     // printf("\e[92mduplicate_paths\e[0m\n");
//     int i;
//     int dup;

//     i = -1;
//     dup = 0;
//     while (paths[++i])
//     {
//         dup = get_duplicate(paths[i], paths);
//         if (dup)
//             paths[i]->flow = dup;
//     }
// }

int main(int ac, char **av)
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
    // printf("step_4\n");
    get_paths(&lemin);
    lemin.size = lemin.ants;
    lemin_play(&lemin);
    lemin_free(&lemin);
    return (EXIT_SUCCESS);
}
