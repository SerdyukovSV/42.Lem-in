/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:38:52 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/08 17:35:04 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	int	ft_nbrlen(intmax_t nbr)
{
	int i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static void	print_space_signed(t_param *pm, int *len, char sign, int zero)
{
	int width;

	(sign) ? pm->t_flag.space = 0 : 0;
	width = pm->width - (*len + zero + (sign ? 1 : 0));
	width -= pm->t_flag.space ? 1 : 0;
	(width < 0) ? width = 0 : 0;
	(pm->t_flag.dot) ? pm->t_flag.zero = 0 : 0;
	*len += width + zero + (sign ? 1 : 0) + (pm->t_flag.space ? 1 : 0);
	(pm->nul == 1 && pm->width) ? width += 1 : 0;
	if (!pm->t_flag.minus)
	{
		while (!pm->t_flag.zero && width-- > 0)
			ft_putchar(32);
		if (pm->t_flag.space || sign)
			ft_putchar(sign ? sign : pm->t_flag.space);
		while ((pm->t_flag.zero && width-- > 0) || zero-- > 0)
			ft_putchar(48);
	}
	else if (pm->t_flag.minus)
		while (width-- > 0)
			ft_putchar(32);
}

static char	*nbr_conversion(intmax_t nbr, int *len)
{
	int			i;
	char		*result;

	i = ft_nbrlen(nbr);
	*len = i;
	if (nbr == INT64_MIN)
		return (ft_strdup("9223372036854775808"));
	if (!(result = ft_memalloc(i)))
		return (0);
	(nbr < 0) ? nbr *= -1 : 0;
	result[i] = '\0';
	while (i-- > 0)
	{
		result[i] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (result);
}

int			print_signed(intmax_t nbr, t_param *pm)
{
	int		len;
	int		zero;
	int		count;
	char	*str;

	pm->nul = ((nbr == 0) && pm->t_flag.dot && !pm->precision) ? 1 : 0;
	str = nbr_conversion(nbr, &len);
	(nbr < 0) ? pm->t_flag.plus = '-' : 0;
	zero = (pm->precision > len ? pm->precision - len : 0);
	if (!pm->t_flag.minus)
		print_space_signed(pm, &len, pm->t_flag.plus, zero);
	count = 0;
	if (pm->t_flag.minus && (pm->t_flag.plus || pm->t_flag.space))
		ft_putchar(pm->t_flag.plus ? pm->t_flag.plus : ' ');
	while (pm->t_flag.minus && count++ < zero)
		ft_putchar(48);
	(!pm->nul) ? ft_putstr(str) : 0;
	if (pm->t_flag.minus)
		print_space_signed(pm, &len, pm->t_flag.plus, zero);
	(pm->nul && !pm->width) ? len = 0 : 0;
	free(str);
	return (len);
}
