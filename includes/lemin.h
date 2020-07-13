#ifndef LEM_IN
# define LEM_IN

# include "../libft/includes/libft.h"
# include <stdio.h>

/*
** Error message
*/

# define ERR            (0)
# define NOARG          (1)
# define INVDLINK       (2)
# define INVDCOMM       (3)
# define INVDROOM       (4)
# define NOPATH         (5)

# define START          "start"
# define END            "end"
# define SIZE           (16384)

int g_id;

/*
** Data structures
*/

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
    int             ant;
    struct s_node   *next;
}                   t_node;

typedef struct      s_links
{
    t_node          **adjace;
    int             *visited;
}                   t_links;

typedef struct      s_rooms
{
    t_node          **hroom;
    t_node          *head;
    t_node          *start;
    t_node          *end;
    int             total;
}                   t_rooms;

typedef struct      s_lemin
{
    int             ants;
    t_rooms         *rooms;
    t_links         *links;
    t_queue         *queue;
    t_node          **paths;
    int             size;
    int             count;

}                   t_lemin;


/*
** functions for receiving and processing data
*/

void        ft_error(int errcode);
void        lm_strdel(char **str);

char        **lemin_read(char *av[]);
int         lemin_validate(char *str[]);
void        lemin_init(t_lemin *lemin, char *str[]);
t_node      **creat_paths(int size);
int         get_ants(char *str);
t_rooms     *get_rooms(char ***str);
t_links     *get_links(t_rooms *room, char **str);

/*
** preparation of data for work on graphs
*/

t_queue     *creat_queue(void);
void        enqueue(t_queue *queue, int value);
int         dequeue(t_queue *queue);

/*
** search for routes to go through an ant farm (BFS algorithm)
*/

t_node      *room_dup(t_node *room);
void        get_paths(t_lemin* lemin, t_links *link, int start);
t_node      **new_paths(t_lemin *lemin, t_node **paths, int start);
void        lem_play(t_lemin *lemin);


#endif