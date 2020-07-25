#include "./includes/lemin.h"

static int  cmp_spurpaths(t_path **spurpaths, t_path *newpath)
{
    int     i;
    int     j;
    int     equal;

    while (*spurpaths)
    {
        i = -1;
        equal = 0;
        while (++i < (*spurpaths)->len)
        {
            j = -1;
            while (++j < newpath->len)
                if (newpath->path[j] == (*spurpaths)->path[i])
                    equal++;
        }
        if (equal == (*spurpaths)->len)
            return (1);
        spurpaths++;
    }
    return (0);
}

int main(int ac, char **av)
{
    // t_path *spur[3];
    // t_path new;

    // spur[0] = malloc(sizeof(t_path *));
    // spur[1] = malloc(sizeof(t_path *));
    // spur[2] = NULL;
    // spur[0]->path[0] = 0;
    // spur[0]->path[1] = 1;
    // spur[0]->path[2] = 2;
    // spur[0]->len = 3;
    // spur[1]->path[0] = 3;
    // spur[1]->path[1] = 4;
    // spur[1]->path[2] = 5;
    // spur[1]->len = 3;
    // new.path[0] = 2;
    // new.path[1] = 1;
    // new.path[2] = 3;
    // new.len = 3;
    // printf("\e[93mcmp = %d\n", cmp_spurpaths(spur, &new));
    char *s = av[1];
    printf("%s\n", av[1]);
    return (0);
}
