/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 01:07:32 by bsalim            #+#    #+#             */
/*   Updated: 2025/05/23 05:02:49 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int parsing(t_data *data,char **av)
{
    data->number_of_philosophers = atoi(av[1]);
    data->time_to_die = atoi(av[2]);
    data->time_to_eat = atoi(av[3]);
    data->time_to_sleep = atoi(av[4]);
    if(data->number_of_philosophers <= 0 || data->number_of_philosophers > 200)
    {
        return -1;
    }
    if(data->time_to_die <= 0 || data->time_to_sleep <= 0 || data->time_to_eat <= 0)
    {
        return -1;
    }
    return 0;
}
