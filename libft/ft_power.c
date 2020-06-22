/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:17:46 by gartanis          #+#    #+#             */
/*   Updated: 2020/01/28 18:15:34 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

long double	ft_power(long double nbr, int n)
{
	if (n == 0)
		return (1);
	if (n < 0)
		return (ft_power(1.0 / nbr, -n));
	return (nbr * ft_power(nbr, n - 1));
}
