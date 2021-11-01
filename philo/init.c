/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 07:30:51 by youkhart          #+#    #+#             */
/*   Updated: 2021/11/01 07:57:47 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (!philo->is_dead || !philo->data->death_occured)
	{
		if (philo->is_dead)
			return (0);
		_eat(philosopher);
		if (philo->is_dead)
			return (0);
		_sleep(philosopher);
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	data->philosophers = (t_philo **)malloc(sizeof(t_philo *) \
		* data->number_of_philosophers);
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
	init_forks(data);
}

void	init_forks(t_data *data)
{
	int	i;
	int	philo_on_left_index;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (i)
			philo_on_left_index = i - 1;
		else
			philo_on_left_index = data->number_of_philosophers - 1;
		data->philosophers[i]->left_fork = \
			&data->philosophers[philo_on_left_index]->right_fork;
		i++;
	}
}

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->death_occured = 0;
	while (i < data->number_of_philosophers)
	{
		if (!i)
			data->init_time = get_time();
		pthread_create(&(data->philosophers[i]->thread), NULL, \
			&start_routine, (void *)(data->philosophers[i]));
		usleep(100);
		i++;
	}
}

void	cleanup(t_data *data)
{
	int	i;

	if (data->philosophers)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_destroy(&(data->philosophers[i]->right_fork));
			free(data->philosophers[i]);
			i++;
		}
		free(data->philosophers);
	}
	pthread_mutex_destroy(&(data->print_mutex));
}
