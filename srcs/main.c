#include "../includes/lemin.h"

void print_paths_all(t_path **paths)
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

void print_path(t_path *path)
{
    int i;

    i = -1;
    if (path)
    {
        // printf("\e[91mPath[%d][%d]:", path->len, path->flow);
        if (path->flow > 0)
            printf("\e[91m");
        printf("Path[%d][%d]:", path->len - 1, path->flow);
        while (++i < path->len)
            printf(" %s", path->node[i]->name);
    }
    printf("\e[0m\n");
}

 int  is_duplicate(t_node *src, t_path *dst)
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

 int  get_duplicate(t_path *src, t_path **all)
{
    // printf("\e[91mget_duplicate\e[0m\n");
    int dup;
    int i;
    int j;

    i = 0;
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

 void duplicate_paths(t_path **paths)
{
    // printf("\e[92mduplicate_paths\e[0m\n");
    int i;
    int dup;

    i = -1;
    dup = 0;
    while (paths[++i])
    {
        dup = get_duplicate(paths[i], paths);
        if (dup)
            paths[i]->flow = dup;
    }
}

int main()
{
    t_lemin lemin;
    int     ret;

    ret = 0;
    init_attributes(&lemin);
    if (!(lemin.str = lemin_read()))
        ft_error(&lemin, ERR);
    if ((ret = lemin_validate(lemin.str)))
        ft_error(&lemin, ret);
    lemin_init(&lemin);

    get_paths(&lemin);

    lemin.size = lemin.ants;
    lemin_play(&lemin);
    lemin_free(&lemin);
    return (EXIT_SUCCESS);
}
