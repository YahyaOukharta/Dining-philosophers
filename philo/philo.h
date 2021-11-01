/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 07:00:36 by youkhart          #+#    #+#             */
/*   Updated: 2021/11/01 07:57:16 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "utils/utils.h"
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					index;
	int					state;
	pthread_mutex_t		*print_mutex;
	pthread_t			thread;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	long long			last_meal_time;
	int					n_meals;
	int					is_dead;
	int					is_eating;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	t_philo			**philosophers;
	long long		init_time;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	print_mutex;
	int				death_occured;
	int				done;
}					t_data;

void				*start_routine(void *philosopher);
void				init_philos(t_data *data);
void				init_forks(t_data *data);
void				init_threads(t_data *data);
void				_sleep(void *philosopher);
void				_eat(void *philosopher);
int					print_usage(void);
int					parse_args(char **args, t_data *data, int optional);
int					print_args_error(int err);
void				kill_everyone(t_data *data);
int					everyone_ate(t_data *data);
int					supervisor(t_data *data);
void				print_status(t_philo *philo, int has_taken_fork);
char				*int_state_to_str(int state);
void				cleanup(t_data *data);

#endif
