/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 19:06:48 by gartanis          #+#    #+#             */
/*   Updated: 2020/08/28 19:09:08 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void	print_flow(t_path **paths)
{
	int i;
	int j;

	i = -1;
	ft_printf("\n\e[95m-----=== Path[ length ][ ants ] ===-----\e[0m\n");
	while (paths[++i])
	{
		j = -1;
		ft_printf("\e[95mPath[%d][%d]\e[0m", paths[i]->len - 1, paths[i]->f);
		while (++j < paths[i]->len)
			ft_printf(" %s", paths[i]->node[j]->name);
		ft_printf("\n");
	}
}

static void	print_paths(t_path **paths)
{
	int i;
	int j;

	i = -1;
	ft_printf("\n\e[93m-------=== Path[ length ] ===-------\e[0m\n");
	while (paths[++i])
	{
		j = -1;
		ft_printf("\e[93mPath[%d]:\e[0m", paths[i]->len - 1);
		while (++j < paths[i]->len)
			ft_printf(" %s", paths[i]->node[j]->name);
		ft_printf("\n");
	}
}

int			print_usage(char *prg)
{
	ft_printf("\e[1mUsage:\e[0m\n");
	ft_printf("%s [-h] [-l] [-e] [-p] [-f] < maps/file.map\n", prg);
	ft_printf("\e[1mOptions:\e[0m\n");
	ft_printf("   -h : To read the manual.\n");
	ft_printf("   -l : Print line counter.\n");
	ft_printf("   -e : Print error description.\n");
	ft_printf("   -p : Print paths.\n");
	ft_printf("   -f : Print stream of ants on paths.\n");
	return (0);
}

void		print_options(t_lemin *lemin)
{
	if (lemin->opt & OPL)
	{
		ft_printf("\n\e[92m-------=== Number of lines ===-------\n");
		ft_printf("%20d\e[0m\n", lemin->count);
	}
	if (lemin->opt & OPP)
		print_paths(lemin->paths);
	if (lemin->opt & OPF)
		print_flow(lemin->paths);
}

int			get_options(t_lemin *lemin, char **str)
{
	int i;

	i = 0;
	if (str[1][i] == '-')
	{
		while (str[1][++i])
		{
			if (str[1][i] == 'h')
				lemin->opt |= OPH;
			else if (str[1][i] == 'l')
				lemin->opt |= OPL;
			else if (str[1][i] == 'e')
				lemin->opt |= OPE;
			else if (str[1][i] == 'p')
				lemin->opt |= OPP;
			else if (str[1][i] == 'f')
				lemin->opt |= OPF;
			else
				return (print_usage(str[0]));
		}
	}
	if (lemin->opt > 0)
		return (1);
	return (print_usage(str[0]));
}
