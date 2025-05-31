/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:39:07 by bsalim            #+#    #+#             */
/*   Updated: 2025/05/31 20:59:31 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
 
long get_current_time()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
int is_sumilation_ok(t_data *data)
{
    int ok;
    pthread_mutex_lock(&data->protect_stop_sumilation);
    ok = !data->flag_stop_sumilation;
    pthread_mutex_unlock(&data->protect_stop_sumilation);
    return ok;
}
void print_(t_philo *philo,long time,char *message)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d %zu %s\n",philo->id,get_current_time() - time, message);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void *routine_philo(void *pointer)
{
    t_philo *philo = (t_philo *)pointer;
    if (!philo || !philo->data || !philo->left_fork || !philo->right_fork) {
        fprintf(stderr, "Error: Philosopher or forks are uninitialized\n");
        return NULL;
    }
    long time = get_current_time();
    while (is_sumilation_ok(philo->data))
    {
        usleep((philo->id % 2 == 0) * 1000);
        print_(philo,time,"thinking");
        if (philo->id % 2 == 0)
        {
            usleep(200);
            pthread_mutex_lock(philo->left_fork);
            print_(philo,time,"pick up left fork");
            pthread_mutex_lock(philo->right_fork);
            print_(philo,time,"pick up right fork");
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            print_(philo,time,"pick up right fork");
            pthread_mutex_lock(philo->left_fork);
            print_(philo,time,"pick up left fork");

        }
        print_(philo,time,"eating");
        usleep(philo->data->time_to_eat);
        pthread_mutex_lock(&philo->data->meals_mutex);
        philo->last_meals = get_current_time();
        philo->meals_eaten++;
        pthread_mutex_unlock(&philo->data->meals_mutex);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        print_(philo,time,"sleep");
        usleep(philo->data->time_to_sleep);
        pthread_mutex_lock(&philo->data->protect_stop_sumilation);
        if(get_current_time() - time > philo->data->time_to_die)
        {
            if(!philo->data->flag_stop_sumilation) 
            {
                philo->data->flag_stop_sumilation = 1;
                print_(philo,time,"die");
            }
            pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
            return NULL;
        }
        pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
    }
    return NULL;
}
