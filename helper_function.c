/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:16:35 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/01 16:15:54 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


long ft_longatol(const char *str)
{
    long result;
    int index;
    int sing;
    index = 0;
    sing = 1;
    result = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\v'|| str[index] == '\f' || str[index] == '\n'|| str[index] == '\r')
    {
        index++;
    }
    if(str[index] == '-' || str[index] == '+')
    {
        if(str[index] == '-')
            sing *= -1;
        index++;
    }
    while(str[index] >= '0' && str[index] <= '9')
    {
        result = result * 10 + (str[index] - '0');
        index++;
    }
    if(result > 2147483647 || result < -2147483648)
    {
        return -1;
    }
    return (result * sing);
}