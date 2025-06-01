/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:01:16 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/01 16:34:57 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int initialization_struct(t_data *data)
{
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!data->forks) {
        fprintf(stderr, "Error: Failed to allocate memory for forks.\n");
        return -1;
    }


    data->philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
    if (!data->philosophers) {
        free(data->forks);
        fprintf(stderr, "Error: Failed to allocate memory for philosophers.\n");
        return -1;
    }

    if (pthread_mutex_init(&data->meals_mutex, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize meals mutex.\n");
        free(data->forks);
        free(data->philosophers);
        return -1;
    }
    // if (pthread_mutex_init(&data->forks[0], NULL) != 0) 
    // {
    //     pthread_mutex_destroy(&data->meals_mutex);
    //     pthread_mutex_destroy(&data->protect_stop_sumilation);
    //     free(data->forks);
    //     free(data->philosophers);
    //     return -1;
    // }

    if (pthread_mutex_init(&data->protect_stop_sumilation, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize stop simulation mutex.\n");
        pthread_mutex_destroy(&data->meals_mutex);
        free(data->forks);
        free(data->philosophers);
        return -1;
    }
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize stop simulation mutex.\n");
        pthread_mutex_destroy(&data->protect_stop_sumilation);
        pthread_mutex_destroy(&data->meals_mutex);
        free(data->forks);
        free(data->philosophers);
        return -1;
    }
    for (int i = 0; i < data->number_of_philosophers; i++) {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0) {
            fprintf(stderr, "Error: Failed to initialize fork %d mutex.\n", i);
            for (int j = 0; j < i; j++)
                pthread_mutex_destroy(&data->forks[j]);
            pthread_mutex_destroy(&data->print_mutex);
            pthread_mutex_destroy(&data->meals_mutex);
            pthread_mutex_destroy(&data->protect_stop_sumilation);
            free(data->forks);
            free(data->philosophers);
            return -1;
        }
    }

    for (int j = 0; j < data->number_of_philosophers; j++) {
        data->philosophers[j].id = j + 1;
        data->philosophers[j].meals_eaten = 0;
        data->philosophers[j].last_meals = 0;
        data->philosophers[j].left_fork = &data->forks[j];
        //  if condition philoNumber == 1 : right_fork = NULL;
        //  else : right_fork = &data->forks[(j + 1) % data->number_of_philosophers];
        data->philosophers[j].right_fork = &data->forks[(j + 1) % data->number_of_philosophers];
        data->philosophers[j].data = data;
    }

    return 0;
}
int create_thread(t_data *data)
{
	int i = 0;
    if (data->number_of_philosophers == 1) 
    {
        print_(data->philosophers,data->philosophers->data->time_to_start,"thinking");
        pthread_mutex_lock(data->philosophers->right_fork);
        print_(data->philosophers,data->philosophers->data->time_to_start,"pick up right fork");
        if(get_current_time() - data->philosophers->data->time_to_start <= data->philosophers->data->time_to_die)
                usleep(data->philosophers->data->time_to_die);
        print_(data->philosophers,data->philosophers->data->time_to_start,"died");
        pthread_mutex_unlock(data->philosophers->right_fork);
        pthread_mutex_destroy(&data->philosophers->data->meals_mutex);
        pthread_mutex_destroy(&data->philosophers->data->protect_stop_sumilation);
        return 0;
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

    data->time_to_start = get_current_time();
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
	while(i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
        i++;
	}
	pthread_mutex_destroy(&data->meals_mutex);
	pthread_mutex_destroy(&data->protect_stop_sumilation);
}