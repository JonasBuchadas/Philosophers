#include "philo.h"

static void	sleeping(t_seat *seat);
static void	thinking(t_seat *seat);

void	*dinner(void *arg)
{
	t_seat	*seat;

	seat = (t_seat *)arg;
	while (!(*seat->finish_dinner || *seat->dead))
	{
		eating(seat);
		sleeping(seat);
		thinking(seat);
	}
	return (NULL);
}

static void	sleeping(t_seat *seat)
{
	if (!(*seat->finish_dinner || *seat->dead))
	{
		message(seat, SLEEP);
		usleep(seat->time_to_sleep * 1000);
	}
}

static void	thinking(t_seat *seat)
{
	if (!(*seat->finish_dinner || *seat->dead))
		message(seat, THINKING);
}
