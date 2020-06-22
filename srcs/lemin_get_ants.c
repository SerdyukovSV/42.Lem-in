/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_get_ants.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:08:38 by marvin            #+#    #+#             */
/*   Updated: 2020/06/20 16:08:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int lemin_get_ants(int fd)
{
    int     nbr;
    char    *line;
    
    nbr = 0;
    if (get_next_line(fd, &line) > 0)
    {
        while (line[nbr])
        {
            if (!ft_isdigit(line[nbr++]))
            {
                free(line);
                line = NULL;
                break;
            }
        }
    }
    nbr = (line != NULL) ? ft_atoi(line) : 0;
    return (nbr);    
}