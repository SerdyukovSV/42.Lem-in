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
            if (lemin->ants == 0 && ret > 1)
                return (0);
            return (lemin->ants);
        }
        else
            break ;
        lemin->count++;
    }
    // if (!str[lemin->count][0])
    //         ft_error(lemin, INVDLINE);
    return (0);
}