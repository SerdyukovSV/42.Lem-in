/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 16:19:30 by gartanis          #+#    #+#             */
/*   Updated: 2020/08/28 16:19:34 by gartanis         ###   ########.fr       */
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
