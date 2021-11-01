/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 07:03:33 by youkhart          #+#    #+#             */
/*   Updated: 2021/11/01 08:08:10 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, int has_taken_fork)
{
	pthread_mutex_lock(philo->print_mutex);
	if (get_time() - philo->data->init_time > 120000000 || \
			get_time() - philo->data->init_time < -120000000)
		return ;
	if (has_taken_fork)
		printf("%.6lld %d has taken a fork\n", get_time() - \
			philo->data->init_time, philo->index + 1);
	else if (philo->is_dead)
	{
		printf("%.6lld %d died\n", get_time() - \
			philo->data->init_time, philo->index + 1);
		kill_everyone(philo->data);
		return ;
	}
	else
		printf("%.6lld %d is %s\n", get_time() - philo->data->init_time, \
			philo->index + 1, int_state_to_str(philo->state));
	pthread_mutex_unlock(philo->print_mutex);
}

void	_sleep(void *philosopher)
{
	if (((t_philo *)philosopher)->is_dead)
		return ;
	((t_philo *)philosopher)->state = 2;
	print_status(((t_philo *)philosopher), 0);
	my_sleep(((t_philo *)philosopher)->data->time_to_sleep);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, 1);
	if (philo->is_dead)
		return (0);
	pthread_mutex_lock(&philo->right_fork);
	print_status(philo, 1);
	if (philo->is_dead)
		return (0);
	return (1);
}

void	_eat(void *philosopher)
{
	t_philo	*philo;

	if (((t_philo *)philosopher)->is_dead)
		return ;
	philo = (t_philo *)philosopher;
	philo->state = 0;
	print_status(philo, 0);
	if (philo->is_dead)
		return ;
	if (!take_forks(philo))
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

int	main(int ac, char **av)
{
	t_data	data;
	int		err;
	int		supervisor_status;

	if (ac < 5 || ac > 6)
		return (print_usage());
	err = parse_args(av + 1, &data, ac == 6);
	if (err)
		return (print_args_error(err));
	init_philos(&data);
	init_threads(&data);
	while (1)
	{
		supervisor_status = supervisor(&data);
		if (supervisor_status)
			break ;
	}
	cleanup(&data);
	return (0);
}
