/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:01:16 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/12 13:41:57 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo_rine(void *dat)
{
	t_philo *philo = (t_philo*)dat;
	if (philo->data->number_of_philosophers == 1) 
	{
		print_(philo->data->philosophers,
			philo->data->philosophers->data->time_to_start, "is thinking");
		pthread_mutex_lock(philo->data->philosophers->right_fork);
		print_(philo->data->philosophers, philo->data->philosophers->data->time_to_start,
			"has taken a fork");
		usleep(philo->data->philosophers->data->time_to_die * 1000);
		print_(philo->data->philosophers,
			philo->data->philosophers->data->time_to_start, "died");
		pthread_mutex_unlock(philo->data->philosophers->right_fork);
		return (NULL);
	}
	return NULL;
}

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	// if(data->number_of_philosophers == 1)
	// {
	// 	pthread_create(&data->philosophers[0].thread, NULL,one_philo_rine, &data->philosophers[0]);
	// 	pthread_join(data->philosophers[0].thread, NULL);
	// 	return 0;
	// }
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
	i = 0;
	// if(data->number_of_philosophers == 1)
	// {
	// 	pthread_create(&data->philosophers[0].thread, NULL,one_philo_rine, &data->philosophers[0]);
	// 	pthread_join(data->philosophers[0].thread, NULL);
	// 	return 0;
	// }
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				routine_philo, &data->philosophers[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(monitor,  NULL) != 0)
			return (-1);
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
