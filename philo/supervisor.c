/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 07:29:18 by youkhart          #+#    #+#             */
/*   Updated: 2021/11/01 07:39:29 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_everyone(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo = data->philosophers[i];
		philo->is_dead = 1;
		i++;
	}
}

int	everyone_ate(t_data *data)
{
	int	i;

	i = 0;
	if (data->death_occured)
		return (0);
	if (!data->number_of_times_each_philosopher_must_eat)
		return (0);
	while (i < data->number_of_philosophers)
	{
		if (data->death_occured)
			return (0);
		if (data->philosophers[i]->n_meals < \
			data->number_of_times_each_philosopher_must_eat)
			return (0);
		i++;
	}
	data->death_occured = 1;
	return (1);
}

int	supervisor(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo = data->philosophers[i];
		if (get_time() - philo->data->init_time - \
			philo->last_meal_time >= philo->data->time_to_die)
		{
			philo->is_dead = 1;
			print_status(philo, 0);
			philo->data->death_occured = 1;
			return (i + 1);
		}
		if (everyone_ate(philo->data))
			return (-1);
		usleep(30);
		i++;
	}
	return (0);
}
