#include "utils.h"

int	ft_atoi(const char *str)
{
	int res;
	int	sign;

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
	{
		res = (res * 10) + *str - '0';
		str++;
	}
	if (res * sign > 0 && sign < 0)
		return (0);
	else if (res * sign < 0 && sign > 0)
		return (-1);
	else
		return (res * sign);
}