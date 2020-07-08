/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_fl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:37:07 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/04 21:29:07 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char				*get_bin(unsigned char c)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * 9)))
		return (0);
	while (c != 0)
	{
		str[i] = "01"[c % 2];
		c /= 2;
		i++;
	}
	while (i != 8)
		str[i++] = '0';
	str[i] = '\0';
	tmp = ft_strrev(str);
	free(str);
	return (tmp);
}

int					get_exponent(char *exp, int len, int correct)
{
	int res;

	res = 0;
	while (len >= 0)
	{
		res += (*exp - 48) * (ft_power(2, len));
		exp += 1;
		len -= 1;
	}
	return (res - correct);
}

static long double	*bintoflt_mant(char *mant, int *len)
{
	int			k;
	long double	*res;

	*len = 1;
	k = -1;
	if (!(res = (long double *)malloc(sizeof(long double) * 64)))
		return (0);
	while (++k < 64)
		res[k] = 0;
	k = 0;
	while (*mant != '\0' && *len <= 64)
	{
		res[k] = (*mant - 48) * (ft_power(2, ((*len) * -1)));
		k++;
		*len += 1;
		mant += 1;
	}
	return (res);
}

static int			*flttodec(long double *src, int *dec, int len)
{
	int i;
	int k;
	int tmp;

	dec[0] = 1;
	dec[1] = 46;
	i = -1;
	while (++i < len)
	{
		k = 2;
		while (src[i])
		{
			src[i] *= 10;
			tmp = (int)src[i];
			dec[k++] += tmp;
			src[i] -= (long double)tmp;
		}
		dec = sort_bigint(dec, &k);
	}
	return (dec);
}

int					*get_mantisa(char *mant, int *len)
{
	int			i;
	long double	*res;
	int			*bin_dec;

	res = bintoflt_mant(mant, &i);
	*len = (i - 1) + 2;
	if (!(bin_dec = (int *)malloc(sizeof(int) * (*len))))
		return (0);
	i = -1;
	while (++i < *len)
		bin_dec[i] = 0;
	bin_dec = flttodec(res, bin_dec, (*len - 2));
	free(res);
	return (bin_dec);
}
