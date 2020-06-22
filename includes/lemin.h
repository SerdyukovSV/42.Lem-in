#ifndef LEM_IN
# define LEM_IN

# include "../libft/includes/libft.h"
# include <stdio.h>

/*
** Error message
*/

# define ERR            "Error"
# define NOARG          "Missing arguments"
# define INVALIDLINK    "Invalid link"

# define SIZE           (1024)

int g_id;

/*
** Data structures
*/
typedef struct      s_path
{
    int             room;
    struct s_path   *next;
}                   t_path;

typedef struct      s_queue
{
    int             items[SIZE];
    int             front;
    int             rear;
}                   t_queue;

typedef struct      s_node
{
    char            *name;
    int             id;
    int             x;
    int             y;
    struct s_node   *next;
}                   t_node;

typedef struct      s_adjrms
{
    t_node          **rooms;
    t_node          **adjrooms;
    int             *visited;
}                   t_adjrms;

typedef struct      s_rooms
{
    t_node          *head;
    t_node          *start;
    t_node          *end;
    int             total;
}                   t_rooms;

typedef struct      s_lemin
{
    int             ants;
    t_rooms         *rooms;
    t_adjrms        *adjrms;
    t_path          **parent;
    t_path          **paths;


}                   t_lemin;


/*
** functions for receiving and processing data
*/

void        ft_error(char *str);
void        lm_strdel(char **str);
t_lemin     *lemin_init(int fd);
int         lemin_get_ants(int fd);
void        lemin_get_rooms(int fd, char *line[], t_rooms *rooms);
void        lemin_get_links(int fd, char *line[], t_lemin *lem);

/*
** preparation of data for work on graphs
*/

void        create_adjrooms(t_rooms *rm, t_adjrms *adj);
void        creat_links(t_node *head, t_adjrms *adj, char *line[]);
t_queue     *creat_queue(void);
void        enqueue(t_queue *queue, int value);
int         dequeue(t_queue *queue);

/*
** search for routes to go through an ant farm (BFS algorithm)
*/

void        breadth_first_search(t_lemin* farm, t_adjrms *adj, int start);


#endif