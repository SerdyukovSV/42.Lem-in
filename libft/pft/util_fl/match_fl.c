/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_fl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:09:23 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/04 19:15:58 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	*shift_sort_bigint(int *src, int len, int count)
{
	int *tmp;
	int k;

	k = 0;
	if (!(tmp = (int *)malloc(sizeof(int) * (len + 1))))
		return (0);
	tmp[k++] = src[count] / 10;
	tmp[k++] = src[count] % 10;
	count = 0;
	while (++count < (len))
		tmp[k++] = (count == (len - 1)) ? 0 : src[count];
	free(src);
	return (tmp);
}

int			*sort_bigint(int *mant, int *len)
{
	int i;

	i = *len;
	while (--i >= 0)
	{
		if (mant[i] != 46 && mant[i] > 9 && (i - 1) >= 0)
		{
			(mant[i - 1] == 46) ? (mant[i - 2] += 1) :\
						(mant[i - 1] += 1);
			mant[i] = mant[i] % 10;
		}
		else if (mant[i] != 46 && mant[i] > 9 && (i - 1) < 0)
		{
			mant = shift_sort_bigint(mant, *len, i);
			*len += 1;
		}
	}
	return (mant);
}

static int	*shift_div_bigint(int *mant, int mod, int *len)
{
	int i;
	int *tmp;
	int tmp2;

	if (!(tmp = (int *)malloc(sizeof(int) * (*len + 1))))
		return (0);
	i = -1;
	tmp2 = mant[*len - 1];
	while (++i < *len)
		tmp[i] = mant[i];
	tmp[i - 1] = 2;
	tmp[i] = mod;
	*len += 1;
	free(mant);
	return (tmp);
}

int			*divide_bigint(int *mant, int exp, int *len)
{
	int i;
	int mod;
	int mod2;

	while (exp++ < 0)
	{
		i = 0;
		mod = (mant[i] % 2 > 0) ? 5 : 0;
		mant[i] = mant[i] / 2;
		while (++i < *len)
		{
			if (mant[i] != 46)
			{
				mod2 = (mant[i] % 2 > 0) ? 5 : 0;
				mant[i] = (mant[i] / 2) + mod;
				mod = mod2;
			}
			if (mod > 0 && (i == (*len - 1)))
			{
				mant = shift_div_bigint(mant, mod, len);
				i++;
			}
		}
	}
	return (mant);
}

int			*multiply_bigint(int *mant, int exp, int *len)
{
	int i;

	while (exp > 0)
	{
		i = 0;
		while (i < *len)
		{
			if (mant[i] == 46)
				i++;
			mant[i] *= 2;
			i++;
		}
		mant = sort_bigint(mant, len);
		exp -= 1;
	}
	return (mant);
}
