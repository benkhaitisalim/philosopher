/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:39:07 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/14 20:50:29 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock (&philo->meal_lock);
	philo->last_meals = get_current_time();
	pthread_mutex_unlock (&philo->meal_lock);
	print_ (philo, philo->data->time_to_start, "is eating");
	ft_usleep (philo->data->time_to_eat);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*secound;

	first = philo->left_fork;
	secound = philo->right_fork;
	pthread_mutex_lock (first);
	print_ (philo, philo->data->time_to_start, "has taken a fork");
	pthread_mutex_lock(secound);
	print_ (philo, philo->data->time_to_start, "has taken a fork");
}

int	one_philo(t_philo *philo)
{
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_(philo, philo->data->time_to_start, "has taken a fork");
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	return (1);
}

void	*routine_philo(void *pointer)
{
	t_philo	*philo;
	long	curr;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	curr = philo->data->time_to_start;
	while (is_sumilation_ok(philo->data))
	{
		if (one_philo(philo) == -1)
			return (NULL);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		think(philo, curr);
		ft_sleep(philo, curr);
		if (most_meals_should_philo_eat(philo) == -1)
			break;
	}
	return (NULL);
}
