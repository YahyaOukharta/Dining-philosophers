#include "utils.h"
#include <stdio.h>
void my_sleep(long long time_in_ms)
{
    
    usleep(time_in_ms/2);
    usleep(time_in_ms/2);

}