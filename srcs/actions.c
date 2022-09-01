#include "philo.h"

void	*dinner(void *arg)
{
	t_seat seat = *(t_seat *)arg;
	printf("Philo no:%i dinning\n", seat.id);
	return (NULL);
}
