#include "utils.h"
#include <stdio.h>

void my_sleep(long long t)
{
    long long start = get_time();
    usleep((t * 1000) - 10000);
    while ((long long)get_time() - start < t);
}