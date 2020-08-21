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
    while (*str != NULL)
    {
        free(*str);
        str += 1;
    }
}

void    links_free(t_links *links)
{
    t_node  *adjacent;
    t_node  *tmp;
    int     i;

    i = -1;
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
    links->visited = NULL;
    adjacent = NULL;
    tmp = NULL;
}

void    rooms_free(t_rooms *rooms)
{
    t_node *tmp;

    while (rooms->head)
    {
        tmp = rooms->head;
        rooms->head = rooms->head->next;
        free(tmp->name);
        free(tmp);
    }
    // rooms->head = NULL;
    rooms->start = NULL;
    rooms->end = NULL;
    tmp = NULL;
}

void    lemin_free(t_lemin *lemin)
{
    int i;

    if (lemin->rooms != NULL)
        rooms_free(lemin->rooms);
    if (lemin->links != NULL)
        links_free(lemin->links);
    i = -1;
    while (lemin->node[++i])
        free(lemin->node[i]);
    lemin->node = NULL;
    i = -1;
    while (lemin->paths[++i])
        free(lemin->node[i]);
    lemin->paths = NULL;
    if (lemin->str)
        lm_strdel(lemin->str);
    lemin->queue = NULL;
    lemin->parent = NULL;
}

void    ft_error2(t_lemin *lemin, int code)
{
    printf("ft_error2\n");
    char *str;

    code = 1;
    lemin_free(lemin);
    // str = get_error(code);
    // if (code >= 0)
        // printf("%s: %s\n", str, str[code]);
    // else
        perror(str);
    exit(EXIT_FAILURE);
}

void    ft_error(int code)
{
    char *str;

    str = get_error(code);
    // if (code >= 0)
    //     printf("%s: %s\n", !code ? "" : str[0], str[code]);
    // else
        perror(str);
    exit(EXIT_FAILURE);
}