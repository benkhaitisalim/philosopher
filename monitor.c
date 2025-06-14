/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:59:35 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/14 16:12:13 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	inside_the_monitor(t_philo *philo, int index)
{
	index = 0;
	while (index < philo->data->number_of_philosophers)
	{
		if (get_current_time() - philo->data->philosophers[index].last_meals
			>= philo->data->time_to_die)
		{
			pthread_mutex_lock (&philo->data->protect_stop_sumilation);
			if (!philo->data->flag_stop_sumilation) 
			{
				philo->data->flag_stop_sumilation = 1;
				print_(philo, philo->data->time_to_start, "died");
			}
			pthread_mutex_unlock (&philo->data->meals_mutexe);
			pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
			return (-1);
		}
		index++;
	}
	return (1);
}

void	*check_dead(void *ptr)
{
	t_philo	*philo;
	int		index;

	philo = (t_philo *)ptr;
	while (1)
	{
		pthread_mutex_lock (&philo->data->meals_mutexe);
		if (inside_the_monitor(philo, index) == -1)
			return (NULL);
		pthread_mutex_unlock(&philo->data->meals_mutexe);
	}
	return (NULL);
}

int	most_meals_should_philo_eat(t_philo *philo)
{
	if (philo->data->most_meals_should_philo_eat > 0)
	{
		pthread_mutex_lock (&philo->data->meals_mutex);
		philo->meals_eaten++;
		if (philo->meals_eaten >= philo->data->most_meals_should_philo_eat)
		{
			pthread_mutex_unlock (&philo->data->meals_mutex);
			return (-1);
		}
	}
	pthread_mutex_unlock(&philo->data->meals_mutex);
	return (1);
}
