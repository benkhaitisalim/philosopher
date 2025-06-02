/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:02:53 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/02 18:57:11 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data {
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long int		time_to_sleep;
	int				most_meals_should_philo_eat;
	int				flag_stop_sumilation;
	long			time_to_start;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	fork;
	pthread_mutex_t	protect_stop_sumilation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meals_mutex;
	struct t_philo	*philosophers;
}	t_data;
typedef struct t_philo{
	int				id;
	int				meals_eaten;
	long int		last_meals;
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
int		create_thread(t_data *data);
long	get_current_time(void);
int		join_pthread(t_data *data);
void	free_pthread(t_data *data);
void	philo_eat(t_philo *philo);
void	print_(t_philo *philo, long int time, char *message);
int		check_dead(t_philo *philo);
int		most_meals_should_philo_eat(t_philo *philo);
int		is_sumilation_ok(t_data *data);
int		one_philo_rotine(t_data *data);
#endif