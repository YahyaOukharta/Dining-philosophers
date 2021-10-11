#include "philo.h"

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
    data->number_of_times_each_philosopher_must_eat = 0;
    if(optional)
    {
        if ((arg = ft_atoi(args[4])) <= 0)
            return(5);
        data->number_of_times_each_philosopher_must_eat = arg;
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