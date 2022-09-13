#include "philo_bonus.h"

static void	sleeping(t_seat *seat);

void	*dinner(void *arg)
{
	t_seat	*seat;

	seat = (t_seat *)arg;
	while (!(*seat->finish_dinner || *seat->dead))
	{
		eat(seat);
		sleeping(seat);
		message(seat, THINKING);
	}
	return (NULL);
}

static void	sleeping(t_seat *seat)
{
	if (!*seat->dead)
	{
		message(seat, SLEEP);
		usleep(seat->time_to_sleep * 1000);
	}
}
