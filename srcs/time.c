#include "philo.h"

int	get_current_time(void)
{
	struct timeval cur_time;

	gettimeofday(&cur_time, NULL);
	printf("seconds : %ld\nmicro seconds : %ld\n",
		   cur_time.tv_sec, cur_time.tv_usec);
	return (0);
}
