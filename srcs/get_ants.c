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

int get_ants(t_lemin *lemin, char **str)
{
    int ret;
    
    ret = 0;
    while (str[lemin->count])
    {
        if (is_command(str[lemin->count]) == 1)
            ;
        else if ((ret = is_ant(str[lemin->count])))
        {
            lemin->ants = ft_atoi(str[lemin->count]);
            if (lemin->ants > MAX_ANTS)
                ft_error(lemin, TOOMANYANT);
            else if (lemin->ants == 0 && ret > 1)
                ft_error(lemin, INVDANTS);
            return (lemin->ants);
        }
        else
            break ;
        lemin->count++;
    }
    return (0);
}