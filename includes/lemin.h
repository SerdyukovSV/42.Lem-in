/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 19:26:35 by gartanis          #+#    #+#             */
/*   Updated: 2020/08/28 19:33:27 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/includes/libft.h"
# include <stdio.h>

/*
** Options
*/

# define OPH			(1 << 0)
# define OPL			(1 << 1)
# define OPE			(1 << 2)
# define OPP			(1 << 3)
# define OPF			(1 << 4)

/*
** Error message
*/

# define ERR			(0)
# define EMPTYFILE		(1)
# define INVDLINK		(2)
# define NOPATH			(3)
# define DUPCOMM		(4)
# define DUPROOM		(5)
# define INVDLINE		(6)
# define INVDANTS		(7)
# define NOTSRCSINK		(8)
# define NOARG			(9)
# define EMPTYLINE		(10)
# define DUPCOORD		(11)
# define TOOMANYANT		(12)
# define INVDCHAR		(13)

# define START			(14)
# define END			(15)

# define SIZE			(16384)
# define MAX_ANTS		(99999)

# define SET			(1)
# define DEL			(0)
# define INCREASE		(1)
# define DECREASE		(-1)

int g_id;

/*
** Data structures
*/

typedef struct		s_node
{
	char			*name;
	int				id;
	int				x;
	int				y;
	int				ant;
	int				capacity;
	int				previous;
	int				is_start;
	int				in_path;
	struct s_node	*next;
}					t_node;

typedef struct		s_path
{
	int				len;
	int				flow;
	int				f;
	t_node			*node[256];
}					t_path;

typedef struct		s_queue
{
	t_node			*items[SIZE];
	int				front;
	int				rear;
}					t_queue;

typedef struct		s_links
{
	t_node			**adjace;
	int				*visited;
}					t_links;

typedef struct		s_rooms
{
	t_node			*head;
	t_node			*start;
	t_node			*end;
	int				total;
	int				pos;
}					t_rooms;

typedef struct		s_lemin
{
	int				opt;
	int				ants;
	int				start;
	int				final;
	t_rooms			*rooms;
	t_links			*links;
	t_node			**node;
	t_path			**paths;
	t_queue			*queue;
	int				*parent;
	int				size;
	int				count;
	char			**str;
}					t_lemin;

/*
** initialization lemin
*/

void				init_attributes(t_lemin *lemin);
void				lemin_init(t_lemin *lemin);
char				**lemin_read(t_lemin *lemin);
int					get_ants(t_lemin *lemin, char **str);
t_rooms				*get_rooms(t_lemin *lemin, char **str);
t_links				*get_links(t_lemin *lemin, char **str);
t_node				*room_dup(t_node *room);
int					lemin_validate(char *str[]);

/*
** Options lemin
*/

int					get_options(t_lemin *lemin, char **str);
void				print_options(t_lemin *lemin);
int					print_usage(char *prg);

/*
** validate lemin
*/

int					is_ant(char *str);
int					is_room(char *str);
int					is_link(char *str);
int					is_command(char *str);
int					is_emptyline(char *str, int size);

/*
** search paths
*/

void				get_paths(t_lemin *lemin);
t_path				*search_path(t_lemin *lemin, t_node *src);

/*
** utility search paths
*/

void				rebuildgraph(t_lemin *lemin, t_path *path, int set);
void				reset_graph(t_lemin *lemin);
void				set_attributes(t_lemin *lemin, t_path **paths);
void				set_capacity(t_lemin *lemin, t_node *src, \
											t_node *dst, int set);
void				sort_paths(t_path **paths);
int					get_flow(t_path **paths, int ants);

/*
** run ants
*/

void				lemin_play(t_lemin *lemin);

/*
** error management
*/

void				ft_error(t_lemin *lemin, int code);
void				links_free(t_links *links, int size);
void				rooms_free(t_rooms *rooms);
void				paths_free(t_path **paths);
void				lemin_free(t_lemin *lemin);

#endif
