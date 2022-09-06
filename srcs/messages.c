#include "philo.h"

void message(t_seat *seat, int status)
{
	pthread_mutex_lock(seat->message);
	if (status == THINKING)
		printf("timestamp_in_ms %d is thinking\n", seat->id);
	if (status == FORK)
		printf("timestamp_in_ms %d has taken a fork\n", seat->id);
	if (status == EAT)
		printf("timestamp_in_ms %d is eating\n", seat->id);
	if (status == SLEEP)
		printf("timestamp_in_ms %d is sleeping\n", seat->id);
	if (status == DEATH)
		printf("timestamp_in_ms %d died\n", seat->id);
	pthread_mutex_unlock(seat->message);
}
