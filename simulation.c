/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:39:07 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/01 16:58:34 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
 
long get_current_time()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
void *routine_philo(void *pointer)
{
    t_philo *philo = (t_philo *)pointer;
    if(philo->id % 2 == 0)
        usleep(1000);
    while (is_sumilation_ok(philo->data))
    {
        print_(philo,philo->data->time_to_start,"thinking");
        philo_eat(philo);
        if(most_meals_should_philo_eat(philo) == -1)
        {
            return NULL;
        }
        print_(philo,philo->data->time_to_start,"sleep");
        usleep(philo->data->time_to_sleep);
        if(check_dead(philo) == -1)
            return (NULL);
        pthread_mutex_unlock(&philo->data->protect_stop_sumilation);
    }
    return NULL;
}
