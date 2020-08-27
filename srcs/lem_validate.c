/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:34:00 by gartanis          #+#    #+#             */
/*   Updated: 2020/08/27 21:35:05 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int	is_command(char *str)
{
	if (str[0] == '#')
	{
		if (str[1] == '#')
		{
			if (!ft_strcmp(str, "##start"))
				return (START);
			else if (!ft_strcmp(str, "##end"))
				return (END);
		}
		return (1);
	}
	return (0);
}

int	is_link(char *str)
{
	int i;

	i = 0;
	if (ft_wordcount(str, '-') == 2)
	{
		if (!ft_strchr(str, ' '))
			return (1);
	}
	return (0);
}

int	is_room(char *str)
{
	char *s;

	if (ft_wordcount(str, ' ') == 3)
	{
		if (*str == 'L' || ft_strchr(str, '-'))
			return (0);
		s = ft_strchr(str, ' ') + 1;
		while (ft_isdigit(*s) || *s == ' ' || *s == '\t')
			s++;
		if (*s == '\0')
			return (1);
	}
	return (0);
}

int	is_ant(char *str)
{
	int i;

	i = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (str[i] == '+')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i);
}

int	is_emptyline(char *str, int size)
{
	int i;

	i = 0;
	if (str[i] == 10)
		return (EMPTYLINE);
	while (i < size && str[i])
	{
		if (str[i] == 10 && str[i + 1] == 10)
			return (EMPTYLINE);
		i++;
	}
	return (0);
}
