#include "../includes/lemin.h"

static char *get_error(int code)
{
    static char *error[] = {
        [ERR] = "ERROR",
        [NOARG] = "missing argument",
        [INVDLINK] = "Invalid link",
        [INVDCOMM] = "Invalid command",
        [INVDROOM] = "Invalid room",
        [NOPATH] = "No paths"
    };
    return (error[code]);
}

void        lm_strdel(char **str)
{
    printf("\e[91mlm_strdel\e[0m\n");
    while (*str != NULL)
    {
        free(*str);
        str += 1;
    }
}

void        links_free(t_links *links)
{
    // printf("\e[91mlinks_free\e[0m\n");
    t_node  *adjacent;
    t_node  *tmp;
    int     i;

    i = -1;
    tmp = NULL;
    adjacent = NULL;
    while (links->adjace[++i])
    {
        adjacent = links->adjace[i];
        while (adjacent)
        {
            tmp = adjacent;
            adjacent = adjacent->next;
            tmp->name = NULL;
            free(tmp);
        }
        links->adjace[i] = NULL;
    }
    free(links->adjace);
    // free(links);
    links->visited = NULL;
}

void        rooms_free(t_rooms *rooms)
{
    // printf("\e[91mrooms_free\e[0m\n");
    t_node *tmp;

    tmp = NULL;
    while (rooms->head)
    {
        tmp = rooms->head;
        rooms->head = rooms->head->next;
        free(tmp->name);
        tmp->name = NULL;
        free(tmp);
    }
    // free(rooms);
    rooms->head = NULL;
    rooms->start = NULL;
    rooms->end = NULL;
    tmp = NULL;
}

void        lemin_free(t_lemin *lemin)
{
    printf("\e[91mlemin_free\e[0m\n");
    int i;

    if (lemin->rooms)
    {
        rooms_free(lemin->rooms);
        free(lemin->rooms);
    }
    if (lemin->links)
    {
        links_free(lemin->links);
        free(lemin->links);
    }
    if (lemin->node)
        free(lemin->node);
    if (lemin->paths)
    {
        i = -1;
        while (lemin->paths[++i])
            free(lemin->paths[i]);
        free(lemin->paths);
    }
    if (lemin->str)
    {
        free((*lemin->str));
        free(lemin->str);
    }
}

void        ft_error(t_lemin *lemin, int code)
{
    // printf("ft_error\n");
    lemin_free(lemin);
    init_attributes(lemin);
    if (code != ERR)
        printf("ERROR: %s\n", get_error(code));
    else
        perror("ERROR");
    exit(EXIT_FAILURE);
}
