/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 00:24:12 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/02 23:44:44 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	unsigned_nbr(t_param *param, va_list args)
{
	int len;

	if (param->modifier & H)
		len = print_unsigned((unsigned short)va_arg(args, unsigned int), param);
	else if (param->modifier & HH)
		len = print_unsigned((unsigned char)va_arg(args, unsigned int), param);
	else if (param->modifier & L)
		len = print_unsigned(va_arg(args, unsigned long), param);
	else if (param->modifier & LL)
		len = print_unsigned(va_arg(args, unsigned long long), param);
	else
		len = print_unsigned(va_arg(args, unsigned int), param);
	return (len);
}

static int	signed_nbr(t_param *param, va_list args)
{
	int len;

	len = 0;
	if (param->modifier & H)
		len = print_signed((short)va_arg(args, int), param);
	else if (param->modifier & HH)
		len = print_signed((char)va_arg(args, int), param);
	else if (param->modifier & L)
		len = print_signed(va_arg(args, long), param);
	else if (param->modifier & LL)
		len = print_signed(va_arg(args, long long), param);
	else
		len = print_signed(va_arg(args, int), param);
	return (len);
}

int			print_decimal(t_param *param, va_list args)
{
	int len;

	len = 0;
	if (param->specifier == 'd' || param->specifier == 'i')
		len = signed_nbr(param, args);
	else if (param->specifier == 'u')
		len = unsigned_nbr(param, args);
	return (len);
}
