/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:01:16 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/13 22:16:41 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
	pthread_t monitor;
	if (pthread_create(&monitor, NULL,
				check_dead, &data->philosophers[0]) != 0)
	if (pthread_join(monitor,  NULL) != 0)
			return (-1);
	return (0);
}

int	join_pthread(t_data *data)
{
	int	i;

	i = 0;
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
	free(data->forks);
	free(data->philosophers);

	pthread_mutex_destroy(&data->meals_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->protect_stop_sumilation);
}
