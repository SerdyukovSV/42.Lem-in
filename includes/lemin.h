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

# define DEL             (1)
# define SET             (0)

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

typedef struct      s_path
{
    int             len;
    int             path[256];
    int             flow;
}                   t_path;

typedef struct      s_shortpath
{
    t_path          *rootpath;
    t_path          **spurpaths;
}                   t_shortpath;

typedef struct      s_node
{
    char            *name;
    int             id;
    int             x;
    int             y;
    int             ant;
    int             path;
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
    int             start;
    int             final;
    t_rooms         *rooms;
    t_links         *links;
    t_queue         *queue;
    int             possible;
    int             *visitroom;
    t_shortpath     **shortpaths;
    t_path          **unique;
    int             size;
    int             count;

}                   t_lemin;


/*
** initialization function
*/

void        lemin_init(t_lemin *lemin, char *str[]);
char        **lemin_read(char *av[]);
int         get_ants(char *str);
t_rooms     *get_rooms(char ***str);
t_links     *get_links(t_rooms *room, char **str);
t_node      *room_dup(t_node *room);
int         lemin_validate(char *str[]);

/*
** search paths
*/

void        get_paths(t_lemin* lemin);
t_path      *newpath(int *parent, int fin);
t_path      *pathjoin(t_path *rootpath, t_path *newpath, int cur);

/*
** utility search paths
*/
void        rebuildgraph(t_lemin *lemin, t_shortpath *shortpath, int set);
void        setvertex(t_lemin *lemin, int vertex, int set);
void        setlink_root(t_lemin *lemin, int *rootpath, int set);
void        setlink_spur(t_lemin *lemin, t_path *spurpaths, int root, int set);
void        possible_paths(t_lemin *lemin, t_path *rootpath);
int         cmp_paths(t_path **spurpaths, t_path *newpath);
void        sort_spurpaths(t_shortpath **shortpaths);
void        sort_rootpaths(t_shortpath **shortpaths);
t_queue     *creat_queue(void);
void        enqueue(t_queue *queue, int value);
int         dequeue(t_queue *queue);

/*
** choice paths & utility
*/

void        choice_paths(t_lemin *lemin);
int         is_replace(t_lemin *lemin, t_path *replace, \
                                t_path **tmp, t_path *new);
int         get_steps(t_path **paths, t_path *new, int ant);
int         is_unique(t_path *new, t_path **unique);
int         is_duplicate(t_path *src, t_path *dst);
void        sort_unique(t_path **paths);

/*
** get flow for paths & run ants
*/

int         get_flow(t_path **paths, int ants);
void        set_flow(t_lemin *lemin, int flow);
void        lemin_play(t_lemin *lemin);

/*
** processing errors
*/

void        ft_error(int errcode);
void        lm_strdel(char **str);

////////
void print_paths(t_path *paths, t_lemin *lemin);
void print_paths_all(t_path **paths, t_lemin *lemin);
void print_paths_2(t_lemin *lemin);

#endif