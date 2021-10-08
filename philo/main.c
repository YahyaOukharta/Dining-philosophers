#include "philo.h"

// void _think(void *data)
// {

// }

void print_status(t_philo *philo)
{
    pthread_mutex_lock(philo->print_mutex);
    char *state = (philo->state == 1 ? "eating" : (philo->state == 2 ? "sleeping":"thinking"));
    printf("%lld philo %d is %s\n", get_time() - philo->data->init_time ,philo->index + 1, state);
    pthread_mutex_unlock(philo->print_mutex);
}

void _sleep(void *philosopher)
{
    ((t_philo *)philosopher)->state = 2;
    print_status(((t_philo *)philosopher));
    my_sleep(((t_philo *)philosopher)->data->time_to_sleep);
}

void _eat(void *philosopher)
{
    t_philo *philo;

    philo = (t_philo *)philosopher;
    philo->state = 0;
    print_status(philo);

    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&philo->right_fork);

    philo->state = 1;
    print_status(philo);
    my_sleep(philo->data->time_to_eat);

    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    *start_routine(void *philosopher)
{

    t_philo *philo;

    philo = (t_philo *)philosopher;
    //printf("philo %d \n", philo->index);
    while (1)
    {
        _eat(philosopher);
        _sleep(philosopher);
    }

    return (0);
}

void init_philos(t_data *data)
{
    int i; 

    data->philosophers = (t_philo **)malloc(sizeof(t_philo *) * data->number_of_philosophers);
    i = 0;
    pthread_mutex_init(&(data->print_mutex), NULL);
    while (i < data->number_of_philosophers)
    {
        data->philosophers[i] = (t_philo *)malloc(sizeof(t_philo));
        data->philosophers[i]->index = i;
        data->philosophers[i]->state = 0;
        data->philosophers[i]->print_mutex = &(data->print_mutex);
        pthread_mutex_init(&data->philosophers[i]->right_fork, NULL);
        data->philosophers[i]->data = data;
        i++;
    }
    i = 0;
    while (i < data->number_of_philosophers)
    {
        data->philosophers[i]->left_fork = &data->philosophers[i ? i - 1 : data->number_of_philosophers - 1]->right_fork;
        i++;
    }

}

void init_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        if(!i)
            data->init_time = get_time();
        pthread_create(&(data->philosophers[i]->thread), NULL, &start_routine, (void *)(data->philosophers[i]));
        if(!i % 2)
            usleep(30);
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
    while(1)
    {
        usleep(1000);
    }
    return (0);
}