/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:43:05 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/02 21:46:05 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	print_printf(char specif, t_param *param, va_list args)
{
	int ret;

	ret = 0;
	if (specif == 'c')
		ret = print_char(param, args);
	else if (specif == 's')
		ret = print_string(param, args);
	else if (specif == 'p' || specif == 'x' || specif == 'X')
		ret = print_hexadecimal(param, args);
	else if (specif == 'd' || specif == 'i')
		ret = print_decimal(param, args);
	else if (specif == 'u')
		ret = print_decimal(param, args);
	else if (specif == 'o')
		ret = print_octal(param, args);
	else if (specif == 'f')
		ret = printf_float(args, param);
	return (ret);
}

static int	print_stdout(const char *pf[], va_list args)
{
	t_param	param;

	param.t_flag.plus = 0;
	param.t_flag.minus = 0;
	param.t_flag.space = 0;
	param.t_flag.zero = 0;
	param.t_flag.hash = 0;
	param.width = 0;
	param.precision = 0;
	param.specifier = 0;
	param.t_flag.dot = 0;
	param.modifier = 0;
	if (!(**pf))
		return (PRINT_ERROR);
	else if ((pars_specifier(pf, &param)) != PRINT_ERROR)
		return (print_printf(param.specifier, &param, args));
	return (print_no_specifier(&param, pf));
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		len_out;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		len_out = 0;
		if (*format == '%')
		{
			format++;
			if ((len_out = print_stdout(&format, args)) == PRINT_ERROR)
				break ;
		}
		else
		{
			ft_putchar(*format);
			format++;
			len++;
		}
		len += (len_out != -1) ? len_out : 0;
	}
	va_end(args);
	return (len);
}
