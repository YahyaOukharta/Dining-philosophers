#ifndef __PHILO_H__
# define __PHILO_H__

#include "utils/utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
typedef struct      s_data t_data;

typedef struct      s_philo
{
    int             index;
    int             state; // 0 thinking // 1 eating // 2 sleeping 
    pthread_mutex_t *print_mutex;
    pthread_t       thread;
    pthread_mutex_t right_fork;
    pthread_mutex_t *left_fork;

    long long       last_meal_time;
    int             n_meals;
    int             is_dead;
    int             is_eating;
    pthread_t       monitor_thread;
    t_data          *data;
}                   t_philo;

typedef struct      s_data
{
    t_philo         **philosophers;
    long long       init_time;
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_of_times_each_philosopher_must_eat;
    pthread_mutex_t print_mutex;
    int             death_occured;
    int             done;
}                   t_data;

int print_usage(void);
int parse_args(char **args, t_data *data, int optional);
int print_args_error(int err);

void   kill_everyone(t_data *data);


#endif