/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:39:07 by bsalim            #+#    #+#             */
/*   Updated: 2025/05/23 10:12:24 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
 
long get_current_time()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
// void stop_simulation(t_data *data) {
//     usleep(5000000); 
//     pthread_mutex_lock(&data->protect_stop_sumilation);
//     data->flag_stop_sumilation = 1;
//     pthread_mutex_unlock(&data->protect_stop_sumilation);
// }

void *routine_philo(void *pointer)
{
    t_philo *philo = (t_philo *)pointer;
    if (!philo || !philo->data || !philo->left_fork || !philo->right_fork) {
        fprintf(stderr, "Error: Philosopher or forks are uninitialized\n");
        return NULL;
    }

    int time = get_current_time();
    while (1)
    {
        pthread_mutex_lock(&philo->data->protect_stop_sumilation);
        if(philo->data->flag_stop_sumilation)
        {
            pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
            return NULL;
        }
        pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
    
        printf("%ld %d thinking\n", get_current_time() - time, philo->id);
        usleep(100);
        if (philo->id % 2 == 0) 
        {
            pthread_mutex_lock(philo->left_fork);
            printf("%ld %d pick up left_fork\n", get_current_time() - time, philo->id);
            pthread_mutex_lock(philo->right_fork);
            printf("%zu %d pick up right_fork\n", get_current_time() - time, philo->id);
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            printf("%zu %d pick up right_fork\n",get_current_time() - time, philo->id);
            pthread_mutex_lock(philo->left_fork);
            printf("%zu %d pick up left_fork\n", get_current_time() - time, philo->id);
        }
        printf("%zu %d eat\n",get_current_time() - time, philo->id);
        usleep(philo->data->time_to_eat);
        pthread_mutex_lock(&philo->data->meals_mutex);
        philo->last_meals = get_current_time();
        philo->meals_eaten++;
        pthread_mutex_unlock(&philo->data->meals_mutex);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        printf("%zu %d sleep\n", get_current_time() - time, philo->id);
        usleep(philo->data->time_to_sleep);

        pthread_mutex_lock(&philo->data->protect_stop_sumilation);
        if (get_current_time() - philo->last_meals > philo->data->time_to_die)
        {
            if (!philo->data->flag_stop_sumilation) {
                philo->data->flag_stop_sumilation = 1;
                printf("%zu %d die\n", get_current_time() - time, philo->id);
            }
            pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
            return NULL;
        }
        pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
    }
    return NULL;
}
