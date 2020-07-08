/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:18:34 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/08 17:40:40 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			ft_unbrlen(uintmax_t nbr, int div)
{
	unsigned int i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= div;
		i++;
	}
	return (i);
}

static void	print_space_unsign(t_param *pm, int *len, int zero)
{
	int width;

	width = pm->width - (*len + zero);
	pm->nul ? width += 1 : 0;
	(width < 0) ? width = 0 : 0;
	(pm->t_flag.dot) ? pm->t_flag.zero = 0 : 0;
	*len += width + zero;
	if (!pm->t_flag.minus)
	{
		while (!pm->t_flag.zero && width-- > 0)
			ft_putchar(32);
		while ((pm->t_flag.zero && width-- > 0) || zero-- > 0)
			ft_putchar(48);
	}
	else if (pm->t_flag.minus)
		while (width-- > 0)
			ft_putchar(32);
}

static char	*unbr_conversion(uintmax_t nbr, int *len)
{
	int			i;
	char		*result;

	i = ft_unbrlen(nbr, 10);
	*len = i;
	if (!(result = ft_memalloc(i)))
		return (0);
	result[i] = '\0';
	while (i-- > 0)
	{
		result[i] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (result);
}

int			print_unsigned(uintmax_t nbr, t_param *pm)
{
	int		len;
	int		count;
	int		zero;
	char	*str;

	pm->nul = ((nbr == 0) && pm->t_flag.dot && !pm->precision) ? 1 : 0;
	str = unbr_conversion(nbr, &len);
	zero = pm->precision > len ? pm->precision - len : 0;
	if (!pm->t_flag.minus)
		print_space_unsign(pm, &len, zero);
	count = 0;
	while (pm->t_flag.minus && count++ < zero)
		ft_putchar(48);
	(!pm->nul) ? ft_putstr(str) : 0;
	if (pm->t_flag.minus)
		print_space_unsign(pm, &len, zero);
	(pm->nul && !pm->width) ? len = 0 : 0;
	free(str);
	return (len);
}
