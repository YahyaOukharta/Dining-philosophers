/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 06:44:36 by youkhart          #+#    #+#             */
/*   Updated: 2021/11/01 06:45:10 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <sys/time.h>
# include <unistd.h>

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	get_time(void);
void		my_sleep(long long ms);

#endif
