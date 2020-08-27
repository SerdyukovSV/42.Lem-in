/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pth_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:56:41 by gartanis          #+#    #+#             */
/*   Updated: 2020/08/27 21:58:40 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	reset_graph(t_lemin *lemin)
{
	lemin->queue->front = -1;
	lemin->queue->rear = -1;
	ft_bzero(lemin->parent, sizeof(int) * lemin->rooms->total);
	ft_bzero(lemin->links->visited, sizeof(int) * lemin->rooms->total);
}

int		get_flow(t_path **paths, int ants)
{
	int		ln;
	float	flow1;
	float	flow2;
	int		count;

	ln = 0;
	count = 0;
	flow1 = INT32_MAX;
	flow2 = INT32_MAX;
	while (paths[count])
	{
		ln += paths[count++]->len - 1;
		flow1 = ((float)ln + ants - 1) / count;
		if (flow1 < flow2)
			flow2 = flow1;
		else
			break ;
	}
	return (flow2);
}

void	set_capacity(t_lemin *lemin, t_node *src, t_node *dst, int set)
{
	t_node *tmp;

	tmp = lemin->links->adjace[src->id];
	while (tmp)
	{
		if (tmp->id == dst->id)
		{
			tmp->capacity += set;
			break ;
		}
		tmp = tmp->next;
	}
}

void	set_attributes(t_lemin *lemin, t_path **paths)
{
	t_node	**node;
	int		i;
	int		j;

	i = -1;
	node = lemin->node;
	while (lemin->node[++i])
	{
		node[i]->in_path = 0;
		node[i]->previous = -1;
	}
	i = -1;
	while (paths[++i])
	{
		j = 0;
		while (paths[i]->node[j])
		{
			node[paths[i]->node[j++]->id]->in_path = 1;
			if (paths[i]->node[j])
				node[paths[i]->node[j]->id]->previous = \
									paths[i]->node[j - 1]->id;
		}
	}
}

void	rebuildgraph(t_lemin *lemin, t_path *path, int set)
{
	t_node	**node;
	int		ln;
	int		i;

	i = 0;
	ln = path->len;
	node = path->node;
	while (ln--)
	{
		if (set == SET && (ln - 1) >= 0)
		{
			set_capacity(lemin, node[ln], node[ln - 1], DECREASE);
			set_capacity(lemin, node[ln - 1], node[ln], INCREASE);
		}
		else if (set == DEL && (ln - 1) >= 0)
		{
			set_capacity(lemin, node[ln], node[ln - 1], INCREASE);
			set_capacity(lemin, node[ln - 1], node[ln], DECREASE);
		}
	}
}
