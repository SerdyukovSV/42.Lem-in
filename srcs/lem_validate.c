/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:34:00 by gartanis          #+#    #+#             */
/*   Updated: 2020/07/17 01:33:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int is_command(char *str, int (*f)(const char *, const char *))
{
    if (*str == '#')
    {
        if (*(str + 1) == '#')
        {
            if (!f(str + 2, START) || !f(str + 2, END))
                return (1);
            return (0);
        }
        return (1);
    }
    return (0);
}

static int is_link(char *str)
{
    int i;

    i = 0;
    if (ft_wordcount(str, '-') == 2)
    {
        while (*str)
            if (*str++ == '-')
                i++;
        if (i == 1)
            return (1);
    }
    return (0);
}

static int is_room(char *str)
{
    if (ft_wordcount(str, ' ') == 3)
    {
        str = ft_strchr(str, ' ') + 1;
        while (*str)
            if (ft_isdigit(*str) || *str == ' ')
                str++;
            else
                return (0);
        return (1);
    }
    return (0);
}

static int is_ant(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        if (!ft_isdigit(str[i]))
            return (0);
    if (i)
        return(1);
    return(0);
}

int lemin_validate(char *str[])
{
    int i;

    i = 0;
    if (!is_ant(str[i]))
        return (1);
    while (str[++i])
    {
        if (is_room(str[i]))
            continue ;
        if (is_link(str[i]))
            continue ;
        if (is_command(str[i], ft_strcmp))
            continue ;
        else
            return (1);
    }
    return (0);
}