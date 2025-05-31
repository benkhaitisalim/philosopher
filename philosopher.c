/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:01:16 by bsalim            #+#    #+#             */
/*   Updated: 2025/05/31 20:56:22 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int initialization_struct(t_data *data)
{
    // Allocate memory for forks
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!data->forks) {
        fprintf(stderr, "Error: Failed to allocate memory for forks.\n");
        return -1;
    }

    // Allocate memory for philosopher meal tracking
    data->meals_philo_eats = malloc(sizeof(int) * data->number_of_philosophers);
    if (!data->meals_philo_eats) {
        free(data->forks);
        fprintf(stderr, "Error: Failed to allocate memory for meals_philo_eats.\n");
        return -1;
    }

    data->philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
    if (!data->philosophers) {
        free(data->forks);
        free(data->meals_philo_eats);
        fprintf(stderr, "Error: Failed to allocate memory for philosophers.\n");
        return -1;
    }

    if (pthread_mutex_init(&data->meals_mutex, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize meals mutex.\n");
        free(data->forks);
        free(data->meals_philo_eats);
        free(data->philosophers);
        return -1;
    }
    if (pthread_mutex_init(&data->forks[0], NULL) != 0) 
    {
        pthread_mutex_destroy(&data->meals_mutex);
        pthread_mutex_destroy(&data->protect_stop_sumilation);
        free(data->forks);
        free(data->meals_philo_eats);
        free(data->philosophers);
        return -1;
    }
    if (pthread_mutex_init(&data->protect_stop_sumilation, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize stop simulation mutex.\n");
        pthread_mutex_destroy(&data->meals_mutex);
        free(data->forks);
        free(data->meals_philo_eats);
        free(data->philosophers);
        return -1;
    }

    for (int i = 0; i < data->number_of_philosophers; i++) {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0) {
            fprintf(stderr, "Error: Failed to initialize fork %d mutex.\n", i);
            for (int j = 0; j < i; j++)
                pthread_mutex_destroy(&data->forks[j]);
            pthread_mutex_destroy(&data->meals_mutex);
            pthread_mutex_destroy(&data->protect_stop_sumilation);
            free(data->forks);
            free(data->meals_philo_eats);
            free(data->philosophers);
            return -1;
        }
        data->meals_philo_eats[i] = 0;
    }

    // Initialize philosopher properties
    for (int j = 0; j < data->number_of_philosophers; j++) {
        data->philosophers[j].id = j + 1;
        data->philosophers[j].meals_eaten = 0;
        data->philosophers[j].last_meals = 0;
        data->philosophers[j].left_fork = &data->forks[j];
        data->philosophers[j].right_fork = &data->forks[(j + 1) % data->number_of_philosophers];
        data->philosophers[j].data = data;
    }

    return 0;
}
int create_thread(t_data *data)
{
	int i = 0;
    if(data->number_of_philosophers == 1)
    {
        if(pthread_create(&data->philosophers[i].thread,NULL,routine_philo,&data->philosophers[i]) != 0)
			return -1;
    }
	while(i < data->number_of_philosophers)
	{
		if(pthread_create(&data->philosophers[i].thread,NULL,routine_philo,&data->philosophers[i]) != 0)
			return -1;
		i++;
	}
    return 0;
}
int join_pthread(t_data *data)
{
	int i = 0;
	while(i < data->number_of_philosophers)
	{
		if(pthread_join(data->philosophers[i].thread,NULL) != 0)
			return -1;
		i++;
    }
    return 0;
}
void free_pthread(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->meals_mutex);
	pthread_mutex_destroy(&data->protect_stop_sumilation);
	free(data->forks);
	free(data->philosophers);
	free(data->meals_philo_eats);
}