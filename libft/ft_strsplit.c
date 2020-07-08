/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:09:13 by gartanis          #+#    #+#             */
/*   Updated: 2019/09/22 16:03:35 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	size_t	ft_scount(char const *s, char c)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
			j++;
		while (s[i] != c && s[i + 1])
			i++;
		i++;
	}
	return (j);
}

static	size_t	ft_slen(char const *s, char c)
{
	size_t i;
	size_t ln;

	i = 0;
	ln = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i++])
		ln++;
	return (ln);
}

static	void	ft_clear(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (!s || !(str = (char **)malloc(sizeof(char *) * (ft_scount(s, c) + 1))))
		return (NULL);
	while (j < ft_scount(s, c))
	{
		if (!(str[j] = (char *)malloc(sizeof(char) * (ft_slen(&s[i], c) + 1))))
		{
			ft_clear(str);
			return (NULL);
		}
		k = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
			str[j][k++] = s[i++];
		str[j++][k] = '\0';
	}
	str[j] = NULL;
	return (str);
}
