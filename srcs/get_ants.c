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

int get_ants(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
        {
            return (0);
        }
        i++;
    }
    return (ft_atoi(str));
}