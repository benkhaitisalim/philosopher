# ifndef PHILO_H
# define PHILO_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
typedef struct t_philo t_philo;
typedef struct  {
    int number_of_philosophers; //ARGV[1]
    long time_to_die; // ARG[2]
    long time_to_eat; // ARG[3]
    long time_to_sleep; // ARGV[4]
    int most_meals_should_philo_eat; // ARG[5]
    int flag_stop_sumilation;
    pthread_mutex_t print_mutex;
    pthread_mutex_t fork;
    long time_to_start;
    pthread_mutex_t protect_stop_sumilation;
    pthread_mutex_t *forks;
    pthread_mutex_t meals_mutex;
    t_philo *philosophers;
}t_data;
typedef struct t_philo{
    int id;
    int meals_eaten;
    long last_meals;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
} t_philo;
# endif

/* create  and initialization off threads*/
int	initialization_struct(t_data *data);
long ft_longatol(const char *str);
int parsing(t_data *data,char **av,int ac);
/* rotine philosopher*/
void *routine_philo(void *pointer);
int create_thread(t_data *data);
long get_current_time();
int join_pthread(t_data *data);
void free_pthread(t_data *data);
void philo_eat(t_philo *philo);
void print_(t_philo *philo,long time,char *message);
int check_dead(t_philo *philo);
int most_meals_should_philo_eat(t_philo *philo);
int is_sumilation_ok(t_data *data);