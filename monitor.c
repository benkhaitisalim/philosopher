/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:59:35 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/15 16:13:36 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_dead(t_philo *philo)
{
	printf ("%zu %d %s\n",
		get_current_time() - philo->data->time_to_start,
		philo->id, "died");
}

int	inside_the_monitor(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->data->number_of_philosophers)
	{
		pthread_mutex_lock (&philo->data->philosophers[index].meal_lock);
		if (get_current_time() - philo->data->philosophers[index].last_meals
			>= philo->data->time_to_die)
		{
			pthread_mutex_unlock (&philo->data->philosophers[index].meal_lock);
			pthread_mutex_lock (&philo->data->protect_stop_sumilation);
			if (!philo->data->flag_stop_sumilation) 
			{
				philo->data->flag_stop_sumilation = 1;
				ft_dead(philo);
			}
			pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
			return (-1);
		}
		pthread_mutex_unlock (&philo->data->philosophers[index].meal_lock);
		index++;
	}
	return (1);
}

void	*check_dead(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (inside_the_monitor(philo) == -1)
			break ;
	}
	return (NULL);
}

int	most_meals_should_philo_eat(t_philo *philo)
{
	pthread_mutex_lock (&philo->data->meals_mutex);
	if (philo->data->most_meals_should_philo_eat > 0)
	{
		philo->meals_eaten++;
		if (philo->meals_eaten >= philo->data->most_meals_should_philo_eat)
		{
			if (!philo->data->flag_stop_sumilation)
				philo->data->flag_stop_sumilation = 1;
			pthread_mutex_unlock (&philo->data->meals_mutex);
			return (-1);
		}
	}
	pthread_mutex_unlock(&philo->data->meals_mutex);
	return (1);
}
