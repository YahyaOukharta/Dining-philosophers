#ifndef __UTILS_H__
# define __UTILS_H__
# include <sys/time.h>
# include <unistd.h>
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
long long get_time();
void my_sleep(long long);

#endif