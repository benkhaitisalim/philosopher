/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:02:53 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/15 21:30:42 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_data {
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	int				philo_is_full;
	long			time_to_sleep;
	int				most_meals_should_philo_eat;
	int				flag_stop_sumilation;
	long			time_to_start;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t	think_mutex;
	pthread_mutex_t	mutex_service;
	pthread_mutex_t	protect_stop_sumilation;
	pthread_mutex_t	protect_stop_sumilation1;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meals_mutex;
	struct t_philo	*philosophers;
}	t_data;
typedef struct t_philo{
	int				id;
	int				is_full;
	long			last_meals;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	meals_mutexe;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

/* create  and initialization off threads*/
int		initialization_struct_part1(t_data *data);
int		initialization_struct_part2(t_data *data);
long	ft_longatol(const char *str);
int		parsing(t_data *data, char **av, int ac);
int		init_philos(t_data *data);
int		init_pthread_mutex(t_data *data);
/* rotine philosopher*/
void	*routine_philo(void *pointer);
void	think(t_philo *philo, long curr);
void	ft_sleep(t_philo *philo, long curr);
int		create_thread(t_data *data);
long	get_current_time(void);
int		join_pthread(t_data *data);
void	ft_usleep(long time);
void	free_pthread(t_data *data);
// void	philo_eat(t_philo *philo);
void	print_(t_philo *philo, long time, char *message);
void	*check_dead(void *ptr);
int		most_meals_should_philo_eat(t_philo *philo);
int		is_sumilation_ok(t_data *data);
void	ft_time(t_data *data);

#endif