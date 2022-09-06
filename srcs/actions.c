#include "philo.h"

static void	take_forks(t_seat *seat);
static void	put_fork(t_seat *seat, int fork);
static void	take_fork(t_seat *seat, int fork);

void *dinner(void *arg)
{
	t_seat *seat = (t_seat *)arg;
	while (seat->must_eat != 0)
	{
		message(seat, THINKING);
		take_forks(seat);
		message(seat, EAT);
		if (seat->must_eat > 0)
			seat->must_eat--;
		sleep(1);
		put_fork(seat, LEFT_FORK);
		put_fork(seat, RIGHT_FORK);
		message(seat, SLEEP);
		sleep(1);
	}
	return (NULL);
}

static void take_forks(t_seat *seat)
{
	while (seat->forks_taken == false)
	{
		if (seat->id % 2 == 0)
		{
			take_fork(seat, LEFT_FORK);
			if (*seat->r_f_taken == false)
			{
				take_fork(seat, RIGHT_FORK);
				seat->forks_taken = true;
				message(seat, FORK);
			}
			else
				put_fork(seat, LEFT_FORK);
		}
		else
		{
			take_fork(seat, RIGHT_FORK);
			if (*seat->l_f_taken == false)
			{
				take_fork(seat, LEFT_FORK);
				seat->forks_taken = true;
				message(seat, FORK);
			}
			else
				put_fork(seat, RIGHT_FORK);
		}
	}
}

static void take_fork(t_seat *seat, int fork)
{
	if (fork == LEFT_FORK)
	{
		pthread_mutex_lock(seat->left_fork);
		*seat->l_f_taken = true;
	}
	if (fork == RIGHT_FORK)
	{
		pthread_mutex_lock(seat->right_fork);
		*seat->r_f_taken = true;
	}
}

static void put_fork(t_seat *seat, int fork)
{
	if (fork == LEFT_FORK)
	{
		*seat->l_f_taken = false;
		seat->forks_taken = false;
		pthread_mutex_unlock(seat->left_fork);
	}
	if (fork == RIGHT_FORK)
	{
		*seat->r_f_taken = false;
		seat->forks_taken = false;
		pthread_mutex_unlock(seat->right_fork);
	}
}
