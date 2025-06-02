/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sumilation_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:58:49 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/02 12:53:21 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sumilation_ok(t_data *data)
{
	int	ok;

	pthread_mutex_lock(&data->protect_stop_sumilation);
	ok = !data->flag_stop_sumilation;
	pthread_mutex_unlock(&data->protect_stop_sumilation);
	return (ok);
}

void	print_(t_philo *philo, long time, char *message)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%d %zu %s\n", philo->id, get_current_time() - time, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0) 
	{
		pthread_mutex_lock(philo->left_fork);
		print_(philo, philo->data->time_to_start, "pick up left fork");
		pthread_mutex_lock(philo->right_fork);
		print_(philo, philo->data->time_to_start, "pick up right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_(philo, philo->data->time_to_start, "pick up right fork");
		pthread_mutex_lock(philo->left_fork);
		print_(philo, philo->data->time_to_start, "pick up left fork");
	}
	usleep(philo->data->time_to_eat);
	print_(philo, philo->data->time_to_start, "eating");
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->protect_stop_sumilation);
	if (get_current_time() - philo->data->time_to_start 
		> philo->data->time_to_die)
	{
		if (!philo->data->flag_stop_sumilation) 
		{
			philo->data->flag_stop_sumilation = 1;
			print_(philo, philo->data->time_to_start, "die");
		}
		pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
	return (1);
}

int	most_meals_should_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meals_mutex);
	if (philo->data->most_meals_should_philo_eat > 0)
	{
		philo->last_meals = get_current_time();
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->data->most_meals_should_philo_eat)
		{
			pthread_mutex_unlock (&philo->data->meals_mutex);
			pthread_mutex_destroy(&philo->data->meals_mutex);
			return (-1);
		}
	}
	pthread_mutex_unlock(&philo->data->meals_mutex);
	return (1);
}
