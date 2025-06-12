/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:39:07 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/12 13:46:42 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int		ask_for_place(t_data *data)
{
	pthread_mutex_lock(&data->mutex_service);
	if(data->seaters_on_table >= data->number_of_philosophers - 1)
	{
		pthread_mutex_unlock(&data->mutex_service);
		return 0;
	}
	data->seaters_on_table++;
	pthread_mutex_unlock(&data->mutex_service);

	return 1;
}

void get_up_from_table(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_service);
	philo->data->seaters_on_table--;
	pthread_mutex_unlock(&philo->data->mutex_service);
}
void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork);
	philo->last_meals = get_current_time();
	pthread_mutex_unlock(&philo->data->fork);
	print_(philo, philo->data->time_to_start, "is eating");
	ft_usleep(philo->data->time_to_eat);

}
void put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_t *first;
	pthread_mutex_t *secound;
	if(philo->id % 2 == 0)
	{
		first = philo->left_fork;
		secound = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		secound = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print_(philo, philo->data->time_to_start, "has taken a fork");
	pthread_mutex_lock(secound);
	print_(philo, philo->data->time_to_start, "has taken a fork");
}
void	*routine_philo(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if(philo->id % 2 == 0)
	{
		usleep(philo->data->time_to_eat);
	}
	while (is_sumilation_ok(philo->data))
	{
		if(!ask_for_place(philo->data))
		{
			continue;
		}
		pick_up_forks(philo);
		put_down_forks(philo);
		eat(philo);
		get_up_from_table(philo);
		if(most_meals_should_philo_eat(philo)  == -1)
		{
			return NULL;
		}
		long last_meals = philo->data->time_to_die -  (philo->data->time_to_eat + philo->data->time_to_sleep + philo->last_meals);
		print_(philo, philo->data->time_to_start, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_(philo, philo->data->time_to_start, "is thinking");
		if(last_meals > philo->data->time_to_eat)
		{
			ft_usleep(last_meals);
		}
	}
	return (NULL);
}