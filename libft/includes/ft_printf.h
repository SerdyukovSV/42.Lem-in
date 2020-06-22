/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 23:04:43 by gartanis          #+#    #+#             */
/*   Updated: 2020/02/09 16:05:37 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>

/*
** double data structure
*/

typedef struct			s_param
{
	struct				s_flag
	{
		char			plus;
		char			minus;
		char			space;
		char			zero;
		char			hash;
		char			dot;
	}					t_flag;
	int					modifier;
	char				specifier;
	int					width;
	int					precision;
	int					tmp;
	int					nul;
}						t_param;

# define PRINT_ERROR	-1
# define SPECIFIER		"cspdiouxXf"
# define FLAGS			"+- #0"
# define PREFIX 		"0x"
# define PREFIX_UP 		"0X"
# define SPEC_LEN		10

# define PLUS			'+'
# define MINUS			'-'
# define SPACE			' '
# define HASH			'#'
# define ZERO			'0'
# define DOT			'.'
# define PERCENT		'%'

# define SPEC_C			'c'
# define SPEC_S			's'
# define SPEC_P			'p'
# define SPEC_D			'd'
# define SPEC_I			'i'
# define SPEC_O			'o'
# define SPEC_U			'u'
# define SPEC_LOW_X		'x'
# define SPEC_UP_X		'X'
# define SPEC_F			'f'

# define H				1
# define HH				2
# define L				4
# define LL				8
# define UPP_L			16
# define UPP_D			32

/*
** prototypes of basic functions
*/

int						ft_printf(const char *format, ...);
int						pars_specifier(const char **specif, t_param *param);
int						get_param(const char **pf, t_param *param);
char					verif_sign(t_param *param, intmax_t nbr);
char					*get_bin(unsigned char c);
int						get_exponent(char *exp, int len, int correct);
int						*get_mantisa(char *mant, int *len);
int						*sort_bigint(int *mant, int *len);
int						*divide_bigint(int *mant, int exp, int *len);
int						*multiply_bigint(int *mant, int exp, int *len);
int						ft_unbrlen(uintmax_t nbr, int div);

/*
** prototypes print function
*/

void					print_space(int offset, char flag);
int						find_percent(const char **pf, t_param *pm);
int						print_char(t_param *param, va_list args);
int						print_string(t_param *param, va_list args);
int						print_hexadecimal(t_param *param, va_list args);
int						print_octal(t_param *param, va_list args);
int						print_decimal(t_param *param, va_list args);
int						print_signed(intmax_t nbr, t_param *param);
int						print_unsigned(uintmax_t nbr, t_param *param);
int						printf_float(va_list args, t_param *param);
int						print_no_specifier(t_param *pm, const char **pf);

#endif
