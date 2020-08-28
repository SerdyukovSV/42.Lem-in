/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 22:01:54 by gartanis          #+#    #+#             */
/*   Updated: 2020/08/28 19:13:52 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		sort_paths(t_path **paths)
{
	t_path	*tmp;
	int		i;
	int		j;

	i = -1;
	while (paths[++i])
	{
		j = -1;
		while (paths[++j])
		{
			if (paths[j + 1] && paths[j]->len > paths[j + 1]->len)
			{
				tmp = paths[j];
				paths[j] = paths[j + 1];
				paths[j + 1] = tmp;
			}
		}
	}
}

static void	print_lemin(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(STDOUT_FILENO, &str[i][0], ft_strlen(str[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	write(STDOUT_FILENO, "\n", 1);
}

int			main(int ac, char **av)
{
	t_lemin	lemin;

	init_attributes(&lemin);
	if (ac > 1)
	{
		if (!get_options(&lemin, av))
			return (0);
	}
	if (lemin.opt & OPH)
		return (print_usage(av[0]));
	if (!(lemin.str = lemin_read(&lemin)))
		ft_error(&lemin, ERR);
	lemin_init(&lemin);
	get_paths(&lemin);
	print_lemin(lemin.str);
	lemin.size = lemin.ants;
	lemin.count = 0;
	lemin_play(&lemin);
	print_options(&lemin);
	lemin_free(&lemin);
	return (EXIT_SUCCESS);
}
