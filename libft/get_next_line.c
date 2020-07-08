/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <gartanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:05:25 by gartanis          #+#    #+#             */
/*   Updated: 2019/10/28 15:37:40 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	int		gnl_check_line(char **stack, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *stack;
	while (tmp[i] != '\n')
	{
		if (!(tmp[i++]))
			return (0);
	}
	tmp[i] = '\0';
	*line = ft_strdup(*stack);
	*stack = ft_strdup(&tmp[i] + 1);
	free(tmp);
	return (1);
}

static	int		gnl_read_file(int fd, char **stack, char *tmp, char **line)
{
	int		ret;
	char	*tmp_stack;

	while ((ret = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		tmp[ret] = '\0';
		if (*stack)
		{
			tmp_stack = *stack;
			*stack = ft_strjoin(tmp_stack, tmp);
			free(tmp_stack);
			tmp_stack = NULL;
		}
		else
			*stack = ft_strdup(tmp);
		if (gnl_check_line(stack, line))
			break ;
	}
	return ((ret > 0) ? 1 : 0);
}

int				get_next_line(int const fd, char **line)
{
	int			ret;
	static char	*stack[1024];
	char		*tmp;

	if ((fd < 0 || fd > 1024) || !line || (read(fd, stack[fd], 0) < 0))
		return (-1);
	if (stack[fd] && (gnl_check_line(&stack[fd], line)))
		return (1);
	if (!(tmp = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	ret = gnl_read_file(fd, &stack[fd], tmp, line);
	free(tmp);
	if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!ret && *line)
			*line = NULL;
		return (ret);
	}
	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}
