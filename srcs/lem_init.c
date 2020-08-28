/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:23:16 by gartanis          #+#    #+#             */
/*   Updated: 2020/08/27 21:23:20 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static t_node	**create_node(t_rooms *room)
{
	t_node	*head;
	t_node	**node;

	if (!room)
		return (NULL);
	head = room->head;
	if (!(node = malloc(sizeof(t_node *) * (room->total + 1))))
		return (NULL);
	while (head)
	{
		node[head->id] = head;
		head = head->next;
	}
	node[room->total] = NULL;
	head = NULL;
	return (node);
}

static int		get_countpath(t_lemin *lemin)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = lemin->links->adjace[lemin->start];
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

static int		check_rooms(t_node **node)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (node[++i])
	{
		k = i;
		j = -1;
		while (node[++j])
		{
			if (j != k && !ft_strcmp(node[j]->name, node[k]->name))
				return (DUPROOM);
			if (j != k && (node[j]->x == node[k]->x) && \
					(node[j]->y == node[k]->y))
				return (DUPCOORD);
		}
	}
	return (0);
}

void			init_attributes(t_lemin *lemin)
{
	g_id = 0;
	lemin->opt = 0;
	lemin->ants = 0;
	lemin->size = 0;
	lemin->count = 0;
	lemin->final = 0;
	lemin->start = 0;
	lemin->str = NULL;
	lemin->node = NULL;
	lemin->rooms = NULL;
	lemin->links = NULL;
	lemin->paths = NULL;
	lemin->queue = NULL;
	lemin->parent = NULL;
}

void			lemin_init(t_lemin *lemin)
{
	int ret;

	if ((ret = get_ants(lemin, lemin->str)) == 0)
		ft_error(lemin, INVDANTS);
	lemin->rooms = get_rooms(lemin, lemin->str);
	if (!(lemin->node = create_node(lemin->rooms)))
		ft_error(lemin, ERR);
	if ((ret = check_rooms(lemin->node)) > 0)
		ft_error(lemin, ret);
	lemin->links = get_links(lemin, lemin->str);
	if (lemin->str[lemin->count])
		ft_error(lemin, INVDLINE);
	if (!lemin->rooms->head)
		ft_error(lemin, NOARG);
	lemin->size = get_countpath(lemin);
	if (!lemin->rooms->start || !lemin->rooms->end)
		ft_error(lemin, NOTSRCSINK);
	lemin->final = lemin->rooms->end->id;
	lemin->start = lemin->rooms->start->id;
}
