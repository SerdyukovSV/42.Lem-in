/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:16:44 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/03 00:02:08 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		print_space(int width, char flag)
{
	int i;

	i = 0;
	while (i++ < width)
		ft_putchar(flag);
}

int			find_percent(const char **pf, t_param *pm)
{
	int			ret;

	while ((ret = get_param(pf, pm)))
		*pf += ret;
	while (**pf && **pf != '%' && !ft_isalpha(**pf))
		*pf += 1;
	if (**pf && **pf == '%')
		return (1);
	return (0);
}

static int	check_specifier(char *dspecif, const char **pf, t_param *param)
{
	int			i;
	char		*dsp;
	const char	*cp;

	i = 0;
	cp = *pf;
	dsp = dspecif;
	while (*cp && !ft_strchr(dsp, *cp))
	{
		dsp = dspecif;
		if (*cp && *cp == PERCENT)
			return (0);
		else if (*cp && (ft_strchr(FLAGS, *cp) || (ft_isdigit(*cp) || \
				*cp == DOT) || ft_strchr("hlLjz", *cp)))
			cp += 1;
		else
			return (0);
	}
	if (*cp && ft_strchr(dsp, *cp))
		param->specifier = *cp;
	else
		return (0);
	return (1);
}

int			pars_specifier(const char **pf, t_param *param)
{
	int		ret;
	char	*dspecif;

	ret = PRINT_ERROR;
	dspecif = ft_strdup(SPECIFIER);
	if ((check_specifier(dspecif, pf, param)))
	{
		if (ft_strchr(dspecif, **pf))
		{
			*pf += 1;
			free(dspecif);
			return (1);
		}
		while ((ret = get_param(pf, param)))
			*pf += ret;
		param->specifier ? *pf += 1 : 0;
	}
	free(dspecif);
	return (ret);
}
