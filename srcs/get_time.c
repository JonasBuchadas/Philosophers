#include "philo.h"

long long get_current_time(long long start_time)
{
	static struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL + tv.tv_usec / 1000) - start_time);
}
