#include "philo.h"

void	message(t_seat *seat, int status)
{
	pthread_mutex_lock(seat->message);
	if (!*seat->dead)
	{
		if (status == THINKING)
			printf("%lld %d is thinking\n",
				get_current_time(seat->time_started), seat->id);
		if (status == FORK)
			printf("%lld %d has taken a fork\n",
				get_current_time(seat->time_started), seat->id);
		if (status == EAT)
			printf("%lld %d is eating\n",
				get_current_time(seat->time_started), seat->id);
		if (status == SLEEP)
			printf("%lld %d is sleeping\n",
				get_current_time(seat->time_started), seat->id);
		if (status == DEATH)
			printf("%lld %d died\n",
				get_current_time(seat->time_started), seat->id);
	}
	pthread_mutex_unlock(seat->message);
}
