/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrpos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:10:37 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/04 19:54:19 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_strchrpos(const char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	else
		return (0);
}
