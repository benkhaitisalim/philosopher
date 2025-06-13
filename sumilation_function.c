/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sumilation_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:58:49 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/13 22:16:47 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sumilation_ok(t_data *data)
{
	int	ok;

	pthread_mutex_lock (&data->protect_stop_sumilation);
	ok = !data->flag_stop_sumilation;
	data->philosophers->dead = 0;
	pthread_mutex_unlock (&data->protect_stop_sumilation);
	return (ok);
}

void	print_(t_philo *philo, long time, char *message)
{
	pthread_mutex_lock (&philo->data->print_mutex);
		printf ("%zu %d %s\n", get_current_time() - time, philo->id, message);
	pthread_mutex_unlock (&philo->data->print_mutex);
}

void	*check_dead(void *ptr)
{
	t_philo	*philo;

	philo  = (t_philo *)ptr;
	while(1)
	{
		pthread_mutex_lock (&philo->data->meals_mutexe);
		int index = 0;
		while(index < philo->data->number_of_philosophers)
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
				return NULL;
			}
			index++;
		}
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
