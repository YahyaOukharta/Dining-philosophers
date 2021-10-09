#include "philo.h"

// void _think(void *data)
// {

// }

void print_status(t_philo *philo, int has_taken_fork)
{
    pthread_mutex_lock(philo->print_mutex);
    if(has_taken_fork)
        printf("%lld %d has taken a fork\n", get_time() - philo->data->init_time, philo->index + 1);
    else if(philo->is_dead)
        printf("%lld %d died\n", get_time() - philo->data->init_time, philo->index + 1);
    else if(philo->state)
    {
        char *state = (philo->state == 1 ? "eating" : (philo->state == 2 ? "sleeping":"thinking"));
        printf("%lld %d is %s\n", get_time() - philo->data->init_time ,philo->index + 1, state);
    }
    pthread_mutex_unlock(philo->print_mutex);
}

void _sleep(void *philosopher)
{
    ((t_philo *)philosopher)->state = 2;
    print_status(((t_philo *)philosopher), 0);
    my_sleep(((t_philo *)philosopher)->data->time_to_sleep);
}

void _eat(void *philosopher)
{
    t_philo *philo;

    philo = (t_philo *)philosopher;
    philo->state = 0;
    print_status(philo, 0);

    pthread_mutex_lock(philo->left_fork);
    print_status(philo, 1);

    pthread_mutex_lock(&philo->right_fork);
    print_status(philo, 1);

    philo->state = 1;
    philo->last_meal_time = get_time() - philo->data->init_time;
    philo->n_meals++;
    print_status(philo, 0);
    my_sleep(philo->data->time_to_eat);

    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    *monitor_routine(void *philosopher)
{
    t_philo *philo;
    philo = (t_philo *)philosopher;

    while (!philo->data->death_occured)
    {
        if (get_time() - philo->data->init_time - philo->last_meal_time > philo->data->time_to_die)
        {
            philo->is_dead = 1;
            philo->data->death_occured = 1;
            print_status(philo, 0);
            break;
        }
        usleep(100);
    }
    return (0);
}

void    *start_routine(void *philosopher)
{
    t_philo *philo;

    philo = (t_philo *)philosopher;
    pthread_create(&(philo->monitor_thread), NULL, &monitor_routine, philosopher);
    while (1)
    {
        if (philo->data->death_occured)
            return(0);
        _eat(philosopher);
        if (philo->data->death_occured)
            return(0);
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
        data->philosophers[i]->last_meal_time = 0;
        data->philosophers[i]->n_meals = 0;
        data->philosophers[i]->is_dead = 0;
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
    while(!data.death_occured);
    return (0);
}