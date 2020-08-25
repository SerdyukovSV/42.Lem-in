#include "../includes/lemin.h"

void        links_free(t_links *links)
{
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
    links->visited = NULL;
}

void        rooms_free(t_rooms *rooms)
{
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
    rooms->head = NULL;
    rooms->start = NULL;
    rooms->end = NULL;
    tmp = NULL;
}

void        paths_free(t_path **paths)
{
    int i;

    if (paths)
    {
        i = -1;
        while (paths[++i])
            free(paths[i]);
    }
}

void        lemin_free(t_lemin *lemin)
{
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
        paths_free(lemin->paths);
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
    static char *error[] = {
        [ERR] = "ERROR",
        [EMPTYFILE] = "Empty file",
        [INVDLINK] = "Invalid link",
        [NOPATH] = "No paths",
        [DUPCOMM] = "Duplicate command",
        [DUPROOM] = "Duplicate room",
        [INVDLINE] = "Invalid line",
        [INVDANTS] = "Invalid number ants",
        [NOTSRCSINK] = "Start or final not specified",
        [NOARG] = "Missing arguments",
        [EMPTYLINE] = "Empty line"
    };

    lemin_free(lemin);
    init_attributes(lemin);
    if (code != ERR)
        printf("\e[91mERROR: %s\e[0m\n", error[code]);
    else
        perror("ERROR");
    exit(EXIT_FAILURE);
}
