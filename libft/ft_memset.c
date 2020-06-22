/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:45:18 by gartanis          #+#    #+#             */
/*   Updated: 2019/09/23 19:39:41 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *p;

	if (len == 0)
		return (b);
	p = (unsigned char *)b;
	while (len--)
	{
		*p = (unsigned char)c;
		if (len)
			p++;
	}
	return (b);
}
