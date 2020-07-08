/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_txt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 20:47:18 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/09 16:19:20 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	print_no_specifier(t_param *pm, const char **pf)
{
	int	len;

	len = PRINT_ERROR;
	if ((len = find_percent(pf, pm)))
	{
		if (pm->width)
		{
			if (!pm->t_flag.minus)
				print_space(pm->width - len, pm->t_flag.zero ? '0' : ' ');
			ft_putchar('%');
			if (pm->t_flag.minus)
				print_space(pm->width - len, ' ');
		}
		else
			ft_putchar('%');
		*pf += 1;
		len += pm->width > len ? pm->width - len : 0;
	}
	return (len);
}

int	print_string(t_param *pm, va_list args)
{
	char	*str;
	char	*dst;
	int		len;

	if ((str = va_arg(args, char *)) == NULL)
		str = ft_strdup("(null)");
	if (pm->precision != 0)
	{
		if (!(dst = (char *)malloc(sizeof(char) * (pm->precision + 1))))
			return (0);
		if ((dst = ft_strncpy(dst, str, pm->precision)))
			str = dst;
	}
	len = ft_strlen(str);
	(pm->t_flag.dot && pm->precision == 0) ? len = 0 : 0;
	if (pm->width && (pm->t_flag.minus != MINUS))
		print_space(pm->width - len, pm->t_flag.zero ? '0' : ' ');
	if (!(pm->precision == 0 && pm->t_flag.dot == DOT))
		ft_putstr(str);
	if (pm->precision != 0 || !ft_strcmp(str, "(null)"))
		free(str);
	if (pm->width && (pm->t_flag.minus == MINUS))
		print_space(pm->width - len, SPACE);
	len += pm->width > len ? pm->width - len : 0;
	return (len);
}

int	print_char(t_param *pm, va_list args)
{
	char	ch;
	int		len;

	len = sizeof(char);
	ch = va_arg(args, int);
	if (pm->width && (pm->t_flag.minus != MINUS))
		print_space(pm->width - len, pm->t_flag.zero ? '0' : ' ');
	ft_putchar(ch);
	if (pm->width && (pm->t_flag.minus == MINUS))
		print_space(pm->width - len, SPACE);
	len += pm->width > len ? pm->width - len : 0;
	return (len);
}
