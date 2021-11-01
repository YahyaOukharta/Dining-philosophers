/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 06:45:57 by youkhart          #+#    #+#             */
/*   Updated: 2021/11/01 07:50:35 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_usage(void)
{
	write(1, "usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 120);
	return (1);
}

int	parse_args(char **args, t_data *data, int optional)
{
	int	v[5];
	int	i;

	i = 0;
	while (i < 4 + optional)
	{
		v[i] = ft_atoi(args[i]);
		if (v[i] <= 0)
			return (i + 1);
		i++;
	}
	data->number_of_philosophers = v[0];
	data->time_to_die = v[1];
	data->time_to_eat = v[2];
	data->time_to_sleep = v[3];
	data->number_of_times_each_philosopher_must_eat = 0;
	if (optional)
		data->number_of_times_each_philosopher_must_eat = v[4];
	return (0);
}

int	print_args_error(int err)
{
	if (err == 1)
		printf("Error in args: number_of_philosophers must be an integer > 0\n");
	if (err == 2)
		printf("Error in args: time_to_die must be an integer > 0\n");
	if (err == 3)
		printf("Error in args: time_to_eat must be an integer > 0\n");
	if (err == 4)
		printf("Error in args: time_to_sleep must be an integer > 0\n");
	if (err == 5)
		printf("Error in args: number_of_times_each_philosopher_must_eat must be \
an integer > 0\n");
	return (1);
}

char	*int_state_to_str(int state)
{
	if (state == 0)
		return ("thinking");
	if (state == 1)
		return ("eating");
	if (state == 2)
		return ("sleeping");
	return (NULL);
}
