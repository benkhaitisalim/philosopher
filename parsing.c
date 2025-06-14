/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 01:07:32 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/14 21:17:44 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(t_data *data, char **av, int ac)
{
	if (ac == 5)
	{
		data->number_of_philosophers = ft_longatol(av[1]);
		data->time_to_die = ft_longatol(av[2]);
		data->time_to_eat = ft_longatol(av[3]);
		data->time_to_sleep = ft_longatol(av[4]);
	}
	else 
	{
		data->number_of_philosophers = ft_longatol(av[1]);
		data->time_to_die = ft_longatol(av[2]);
		data->time_to_eat = ft_longatol(av[3]);
		data->time_to_sleep = ft_longatol(av[4]);
		data->most_meals_should_philo_eat = ft_longatol(av[5]);
		if (data->most_meals_should_philo_eat <= 0)
			return (-1);
	}
	data->time_to_start = get_current_time();
	if (data->number_of_philosophers <= 0 || data->number_of_philosophers > 200)
		return (-1);
	if (data->time_to_die <= 0 || data->time_to_sleep <= 0
		|| data->time_to_eat <= 0)
		return (-1);
	return (0);
}
