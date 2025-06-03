/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:39:07 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/03 17:37:49 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (one_philo_rotine(philo->data) == -1)
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat);
	while (is_sumilation_ok(philo->data))
	{
		print_(philo, philo->data->time_to_start, "is thinking");
		usleep(philo->data->time_to_eat);
		philo_eat(philo);
		if (most_meals_should_philo_eat(philo) == -1)
			return (NULL);
		print_(philo, philo->data->time_to_start, "is sleeping");
		usleep(philo->data->time_to_sleep);
		if (check_dead(philo) == -1)
			return (NULL);
	}
	return (NULL);
}
