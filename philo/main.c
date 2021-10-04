#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include "utils/utils.h"

typedef struct  s_philo
{
    int         index;
    int         state; // 0 sleeping // 1 thinking // 2 eating 
    int         right_fork;
    pthread_t   *thread;
}               t_philo;

typedef struct  s_data
{
    t_philo     **philosophers;
    int         number_of_philosophers;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         number_of_times_each_philosopher_must_eat;
}               t_data;

int print_usage(void)
{
    write(1, "usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n",120);
    return (1);
}

int parse_args(char **args, t_data *data, int optional)
{
    int arg;

    if ((arg = ft_atoi(args[0])) <= 0)
        return(1);
    data->number_of_philosophers = arg;
    if ((arg = ft_atoi(args[1])) <= 0)
        return(2);
    data->time_to_die = arg;
    if ((arg = ft_atoi(args[2])) <= 0)
        return(3);
    data->time_to_eat = arg;
    if ((arg = ft_atoi(args[3])) <= 0)
        return(4);
    data->time_to_sleep = arg;  
    if(optional)
    {
        if ((arg = ft_atoi(args[4])) <= 0)
            return(5);
        data->time_to_sleep = arg;
    }
    return (0);
}
int print_args_error(int err)
{
    //number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
    if (err == 1)
        printf("Error in args: number_of_philosophers must be > 0\n");
    if (err == 2)
        printf("Error in args: time_to_die must be > 0\n");
    if (err == 3)
        printf("Error in args: time_to_eat must be > 0\n");
    if (err == 4)
        printf("Error in args: time_to_sleep must be > 0\n");
    if (err == 5)
        printf("Error in args: number_of_times_each_philosopher_must_eat must be > 0\n");
    return (1);
}

void    *start_routine(void *philosopher)
{
    t_philo *philo;

    philo = (t_philo *)philosopher;
    printf("philo %d \n", philo->index);
    return (0);
}

void init_philos(t_data *data)
{
    int i;

    data->philosophers = (t_philo **)malloc(sizeof(t_philo *) * data->number_of_philosophers);
    i = 0;
    while (i < data->number_of_philosophers)
    {
        data->philosophers[i] = (t_philo *)malloc(sizeof(t_philo));
        data->philosophers[i]->index = i;
        data->philosophers[i]->state = 0;
        data->philosophers[i]->right_fork = 0;
        data->philosophers[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
        i++;
    }
}

void init_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_create(data->philosophers[i]->thread, NULL, &start_routine, (void *)(data->philosophers[i]));
        i++;
    }
}

int main(int ac, char ** av)
{
    t_data data;
    int err;
    if (ac < 5 || ac > 6)
        return (print_usage());
    else if((err = parse_args(av + 1, &data, ac == 6)))
        return (print_args_error(err));
    init_philos(&data);
    init_threads(&data);

    // pthread_create(pthread_t * thread, 
    //                const pthread_attr_t * attr, 
    //                void * (*start_routine)(void *), 
    //                void *arg)

    return (0);
}