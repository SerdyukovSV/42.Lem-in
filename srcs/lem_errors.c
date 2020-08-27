/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:02:35 by gartanis          #+#    #+#             */
/*   Updated: 2020/08/27 21:02:58 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	links_free(t_links *links, int size)
{
	t_node	*adjacent;
	t_node	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	adjacent = NULL;
	while (++i < (size + 1))
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

void	rooms_free(t_rooms *rooms)
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

void	paths_free(t_path **paths)
{
	int i;

	if (paths)
	{
		i = -1;
		while (paths[++i])
			free(paths[i]);
	}
}

void	lemin_free(t_lemin *lemin)
{
	if (lemin->links)
	{
		links_free(lemin->links, lemin->rooms->total);
		free(lemin->links);
	}
	if (lemin->rooms)
	{
		rooms_free(lemin->rooms);
		free(lemin->rooms);
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

void	ft_error(t_lemin *lemin, int code)
{
	static char	*error[] = {
		[ERR] = "\e[91mERROR: ",
		[EMPTYFILE] = "Empty file\e[0m",
		[INVDLINK] = "Invalid link\e[0m",
		[NOPATH] = "No paths\e[0m",
		[DUPCOMM] = "Duplicate command\e[0m",
		[DUPROOM] = "Duplicate room\e[0m",
		[INVDLINE] = "Invalid line\e[0m",
		[INVDANTS] = "Invalid number ants\e[0m",
		[NOTSRCSINK] = "Start or final not specified\e[0m",
		[NOARG] = "Missing arguments\e[0m",
		[EMPTYLINE] = "Empty line\e[0m",
		[DUPCOORD] = "Duplicate coordinates\e[0m",
		[TOOMANYANT] = "Too many ants\e[0m"
	};

	lemin_free(lemin);
	if (code != ERR)
	{
		ft_putstr_fd(error[0], STDERR_FILENO);
		ft_putendl_fd(error[code], STDERR_FILENO);
	}
	else
		perror("ERROR");
	exit(EXIT_FAILURE);
}
