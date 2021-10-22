#include "philo.h"

// void _think(void *data)
// {

// }

void print_status(t_philo *philo, int has_taken_fork)
{
    pthread_mutex_lock(philo->print_mutex);
    if(get_time() - philo->data->init_time > 120000000 || get_time() - philo->data->init_time < -120000000)
        return;
    if(has_taken_fork)
        printf("%.6lld %d has taken a fork\n", get_time() - philo->data->init_time, philo->index + 1);
    else if(philo->is_dead)
    {
        printf("%.6lld %d died\n", get_time() - philo->data->init_time, philo->index + 1);
        kill_everyone(philo->data);
        return;
    }
    else
    {
        char *state = (philo->state == 1 ? "eating" : (philo->state == 2 ? "sleeping":"thinking"));
        printf("%.6lld %d is %s\n", get_time() - philo->data->init_time ,philo->index + 1, state);
    }
    pthread_mutex_unlock(philo->print_mutex);
}

void _sleep(void *philosopher)
{
    if (((t_philo *)philosopher)->is_dead)
        return ;
    ((t_philo *)philosopher)->state = 2;
    print_status(((t_philo *)philosopher), 0);
    my_sleep(((t_philo *)philosopher)->data->time_to_sleep);
}

int everyone_ate(t_data *data)
{
    int i = 0;
    if (data->death_occured)
            return (0);
    if (!data->number_of_times_each_philosopher_must_eat)
        return (0);
    while(i < data->number_of_philosophers )
    {
        if (data->death_occured)
            return (0);
        if (data->philosophers[i]->n_meals < data->number_of_times_each_philosopher_must_eat)
            return (0);
        i++;
    }

    data->death_occured = 1;
    return (1);
}

void _eat(void *philosopher)
{
    if (((t_philo *)philosopher)->is_dead)
        return ;
    t_philo *philo;

    philo = (t_philo *)philosopher;
    philo->state = 0;
    print_status(philo, 0); //thiking
    if (philo->is_dead)
        return ;
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, 1);
    if (philo->is_dead)
        return ;
    pthread_mutex_lock(&philo->right_fork);
    print_status(philo, 1); //forks taken
    if (philo->is_dead || philo->is_dead)
        return ;
    philo->state = 1;
    philo->last_meal_time = get_time() - philo->data->init_time;
    philo->n_meals++;
    print_status(philo, 0);
    my_sleep(philo->data->time_to_eat);
    if (philo->is_dead)
        return ;
    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}



//     while (!philo->data->death_occured)
//     {
//         //printf("philo %d time dincr last meal %lld\n", philo->index + 1 , get_time() - philo->data->init_time - philo->last_meal_time);
//         if (philo->state  != 1 &&  get_time() - philo->data->init_time - philo->last_meal_time >= philo->data->time_to_die)
//         {
//             philo->is_dead = 1;
//             print_status(philo, 0);
//             philo->data->death_occured = 1;
//             return (NULL);
//         }
//         if ( everyone_ate(philo->data)) {
//             return (0);
//         }
//         //usleep(20);
//     }
//     return (0);
// }

void    *start_routine(void *philosopher)
{
    t_philo *philo;

    philo = (t_philo *)philosopher;
    while (!philo->is_dead || !philo->data->death_occured)
    {
        if (philo->is_dead)
            return(0);
        _eat(philosopher);
        if (philo->is_dead)
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
    data->death_occured = 0;

    while (i < data->number_of_philosophers)
    {   
        if(!i)
            data->init_time = get_time();
        pthread_create(&(data->philosophers[i]->thread), NULL, &start_routine, (void *)(data->philosophers[i]));
        usleep(100);
        i++;
    }

}

void   kill_everyone(t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        t_philo *philo = data->philosophers[i];
        philo->is_dead = 1;
        i++;
    }
}

int supervisor(t_data *data){
    int i = 0;

    while (i < data->number_of_philosophers)
    {
        t_philo *philo = data->philosophers[i];
        if (get_time() - philo->data->init_time - philo->last_meal_time >= philo->data->time_to_die)
        {
            philo->is_dead = 1;
            print_status(philo, 0);
            philo->data->death_occured = 1;

            return (i+1);
        }
        if (everyone_ate(philo->data)) {
            return (-1);
        }
        usleep(30);
        i++;
    }
    return (0);
}

int main(int ac, char ** av)
{
    t_data data;
    int err;
    int supervisor_status;
    if (ac < 5 || ac > 6)
        return (print_usage());
    else if((err = parse_args(av + 1, &data, ac == 6)))
        return (print_args_error(err));
    init_philos(&data);
    init_threads(&data);
    while (!(supervisor_status = supervisor(&data)));
    printf("exit status %d\n", supervisor_status);
    return (0);
}