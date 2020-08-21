/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:44:59 by gartanis          #+#    #+#             */
/*   Updated: 2020/07/08 18:47:38 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static char	**lem_split(char *str)
{
	char	**tmp;
	int		i;

	i = ft_wordcount(str, '\n');
	if (!(tmp = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (*str)
	{
		tmp[i] = str;
		if ((str = ft_strchr(str, '\n')))
			*str = '\0';
		if (*(str + 1) != '\0')
			str += 1;
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char		**lemin_read()
{
	char	str[BUFF_SIZE + 1];
	char	*s1;
	char	*s2;
	int		ret;

	s1 = NULL;
	while ((ret = read(STDIN_FILENO, str, BUFF_SIZE)) > 0)
	{
		str[ret] = '\0';
		if (!s1)
		{
			if ((s1 = ft_strdup(str)) == NULL)
				return (NULL);
		}
		else
		{
			s2 = s1;
			s1 = ft_strjoin(s2, str);
			free(s2);
			if (s1 == NULL)
				return (NULL);
		}
	}
	return (lem_split(s1));
}
