/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:28:44 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/02 13:28:46 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialization_struct_part1(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
	{
		printf("Error: Failed to allocate memory for forks.\n");
		return (-1);
	}
	data->philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philosophers)
	{
		free(data->forks);
		printf("Error: Failed to allocate memory for philosophers.\n");
		return (-1);
	}
	return (1);
}

int	initialization_struct_part2(t_data *data)
{
	if (pthread_mutex_init(&data->meals_mutex, NULL) != 0)
	{
		printf("Error: Failed to initialize meals mutex.\n");
		pthread_mutex_destroy(&data->meals_mutex);
		free(data->philosophers);
		return (-1);
	}
	if (pthread_mutex_init(&data->protect_stop_sumilation, NULL) != 0)
	{
		printf("Error: Failed to initialize stop simulation mutex.\n");
		pthread_mutex_destroy(&data->protect_stop_sumilation);
		free(data->forks);
		free(data->philosophers);
		return (-1);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0) 
	{
		printf("Error: Failed to initialize stop simulation mutex.\n");
		pthread_mutex_destroy(&data->protect_stop_sumilation);
		pthread_mutex_destroy(&data->meals_mutex);
		free(data->forks);
		free(data->philosophers);
		return (-1);
	}
	return (1);
}

int	init_pthread_mutex(t_data *data)
{
	int	j;
	int	i;

	i = 0;
	while (i < data->number_of_philosophers) 
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			j = 0;
			printf("Error: Failed to initialize fork %d mutex.\n", i);
			while (j < i)
			{
				pthread_mutex_destroy(&data->forks[j]);
				j++;
			}
			pthread_mutex_destroy(&data->print_mutex);
			pthread_mutex_destroy(&data->meals_mutex);
			pthread_mutex_destroy(&data->protect_stop_sumilation);
			free(data->forks);
			free(data->philosophers);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->number_of_philosophers) 
	{
		data->philosophers[j].id = j + 1;
		data->philosophers[j].meals_eaten = 0;
		data->philosophers[j].last_meals = 0;
		data->philosophers[j].left_fork = &data->forks[j];
		data->philosophers[j].right_fork = &data->forks[(j + 1)
			% data->number_of_philosophers];
		data->philosophers[j].data = data;
		j++;
	}
	return (0);
}
