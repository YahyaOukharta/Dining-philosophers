/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 06:41:30 by youkhart          #+#    #+#             */
/*   Updated: 2021/11/01 06:43:01 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	my_sleep(long long t)
{
	long long	start;

	start = get_time();
	usleep((t * 1000) - 10000);
	while ((long long)get_time() - start < t)
	{
	}
}
