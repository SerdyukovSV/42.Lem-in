/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:22:09 by gartanis          #+#    #+#             */
/*   Updated: 2020/01/28 18:15:24 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_dectostr(int *arr, int sign, int len)
{
	int		i;
	int		k;
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * len + 1 + sign)))
		return (0);
	k = -1;
	i = 0;
	(sign == 1) ? str[i++] = 45 : 0;
	while (++k < len)
	{
		str[i] = (arr[k] == 46) ? 46 : arr[k] + 48;
		i++;
	}
	str[i] = '\0';
	return (str);
}
