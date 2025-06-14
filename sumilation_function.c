/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sumilation_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:58:49 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/14 21:03:27 by bsalim           ###   ########.fr       */
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
	if(!philo->data->flag_stop_sumilation)
	{
		printf ("%zu %d %s\n", get_current_time() - time, philo->id, message);
	}
	pthread_mutex_unlock (&philo->data->print_mutex);
}

void	think(t_philo *philo, long curr)
{
	print_(philo, curr, "is thinking");
}

void	ft_sleep(t_philo *philo, long curr)
{
	print_ (philo, curr, "is sleeping");
	ft_usleep (philo->data->time_to_sleep);
}
