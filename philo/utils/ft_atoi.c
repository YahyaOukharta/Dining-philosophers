/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 06:39:59 by youkhart          #+#    #+#             */
/*   Updated: 2021/11/01 06:40:00 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	str_is_all_digits(const char *str)
{
	while (*str && ft_isdigit(*str))
		str++;
	return (*str == 0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	if (!str_is_all_digits(str))
		return (-1);
	sign = 1;
	res = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		res = (res * 10) + *(str++) - '0';
	if (res * sign > 0 && sign < 0)
		return (0);
	else if (res * sign < 0 && sign > 0)
		return (-1);
	else
		return (res * sign);
}
