/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:08:19 by gartanis          #+#    #+#             */
/*   Updated: 2019/09/22 15:36:56 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static	int	ft_net_size(char const *s)
{
	int i;
	int j;

	i = 0;
	while (ft_isspace(s[i]) && s[i] != '\0')
		i++;
	j = ft_strlen(s);
	if (s[i] != '\0')
		while (ft_isspace(s[j - 1]))
			j--;
	return (j - i);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * (ft_net_size(s) + 1))))
		return (NULL);
	while (ft_isspace(s[i]))
		i++;
	j = 0;
	while (j < ft_net_size(s))
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
