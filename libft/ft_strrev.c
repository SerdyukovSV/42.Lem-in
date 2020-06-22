/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:13:32 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/04 20:57:14 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrev(char *src)
{
	char	*dst;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (src[k])
		k++;
	if (!(dst = (char *)malloc(sizeof(char) * k + 1)))
		return (NULL);
	while (--k >= 0)
		dst[i++] = src[k];
	dst[i] = '\0';
	return (dst);
}
