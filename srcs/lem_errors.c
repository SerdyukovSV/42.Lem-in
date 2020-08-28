/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:02:35 by gartanis          #+#    #+#             */
/*   Updated: 2020/08/28 19:13:02 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static char	*get_error(int code)
{
	static char	*error[] = {
		[ERR] = "\e[91mERROR: ",
		[EMPTYFILE] = "Empty file\e[0m",
		[INVDLINK] = "Invalid link\e[0m",
		[NOPATH] = "No paths\e[0m",
		[DUPCOMM] = "Duplicate command\e[0m",
		[DUPROOM] = "Duplicate room\e[0m",
		[INVDLINE] = "Invalid line\e[0m",
		[INVDANTS] = "Invalid number ants\e[0m",
		[NOTSRCSINK] = "Start or final not specified\e[0m",
		[NOARG] = "Missing arguments\e[0m",
		[EMPTYLINE] = "Empty line\e[0m",
		[DUPCOORD] = "Duplicate coordinates\e[0m",
		[TOOMANYANT] = "Too many ants\e[0m"
	};

	return (error[code]);
}

void		ft_error(t_lemin *lemin, int code)
{
	lemin_free(lemin);
	if (code != ERR)
	{
		if (lemin->opt & OPE)
		{
			ft_putstr_fd(get_error(0), STDERR_FILENO);
			ft_putendl_fd(get_error(code), STDERR_FILENO);
		}
		else
			ft_putendl_fd("ERROR", STDERR_FILENO);
	}
	else
		perror("ERROR");
	exit(EXIT_FAILURE);
}
