/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:01:16 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/03 16:35:59 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo_rotine(t_data *data)
{
	if (data->number_of_philosophers == 1) 
	{
		print_(data->philosophers,
			data->philosophers->data->time_to_start, "is thinking");
		pthread_mutex_lock(data->philosophers->right_fork);
		print_(data->philosophers, data->philosophers->data->time_to_start,
			"has taken a fork");
		if (get_current_time() - data->philosophers->data->time_to_start
			<= data->philosophers->data->time_to_die)
			usleep(data->philosophers->data->time_to_die);
		print_(data->philosophers,
			data->philosophers->data->time_to_start, "died");
		pthread_mutex_unlock(data->philosophers->right_fork);
		pthread_mutex_destroy
			(&data->philosophers->data->meals_mutex);
		pthread_mutex_destroy
			(&data->philosophers->data->protect_stop_sumilation);
		return (-1);
	}
	return (1);
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				routine_philo, &data->philosophers[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	join_pthread(t_data *data)
{
	int	i;

	i = 0;
	data->time_to_start = get_current_time();
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->philosophers[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	free_pthread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->meals_mutex);
	pthread_mutex_destroy(&data->protect_stop_sumilation);
}
