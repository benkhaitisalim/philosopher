/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sumilation_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:58:49 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/14 16:16:30 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sumilation_ok(t_data *data)
{
	int	ok;

	pthread_mutex_lock (&data->protect_stop_sumilation);
	ok = !data->flag_stop_sumilation;
	pthread_mutex_unlock (&data->protect_stop_sumilation);
	return (ok);
}

void	print_(t_philo *philo, long time, char *message)
{
	pthread_mutex_lock (&philo->data->print_mutex);
	printf ("%zu %d %s\n", get_current_time() - time, philo->id, message);
	pthread_mutex_unlock (&philo->data->print_mutex);
}

void	think(t_philo *philo, long curr)
{
	pthread_mutex_lock (&philo->data->think_mutex);
	print_(philo, curr, "is thinking");
	pthread_mutex_unlock (&philo->data->think_mutex);
}

void	ft_sleep(t_philo *philo, long curr)
{
	pthread_mutex_lock (&philo->data->sleep_mutex);
	print_ (philo, curr, "is sleeping");
	ft_usleep (philo->data->time_to_sleep);
	pthread_mutex_unlock (&philo->data->sleep_mutex);
}
