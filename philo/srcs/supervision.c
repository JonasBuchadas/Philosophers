#include "philo.h"

static void	is_finished(t_table *t);

void	*supervise_eat(void *arg)
{
	t_table	*t;

	t = (t_table *)arg;
	while (!(t->finish_dinner || t->thread_dead))
	{
		is_finished(t);
		usleep(1000);
	}
	return (NULL);
}

void	*supervise_death(void *arg)
{
	t_table	*t;
	t_seat	*s;
	int		i;

	t = (t_table *)arg;
	while (!(t->finish_dinner || t->thread_dead))
	{
		i = -1;
		while (++i < t->philo_number)
		{
			s = t->seats + i;
			if (timestamp(s->time_started) - s->time_eated > s->time_to_die)
			{
				message(s, DEATH);
				t->thread_dead = true;
			}
		}
	}
	return (NULL);
}

// void	*supervise_priority(void *arg)
// {
// 	t_table		*t;
// 	int 		i;

// 	t = (t_table *)arg;
// 	while (!(t->finish_dinner || t->thread_dead))
// 	{
// 		i = -1;
// 		while (++i < t->philo_number - 1)
// 		{
// 			if (t->seats[i].time_eated > t->seats[i + 1].time_eated)

// 		}
// 		t->seats[i].left_fork = &t->forks[i];
// 		t->seats[i].right_fork = &t->forks[0];
// 	}
// 	return (NULL);
// }

static void	is_finished(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_number)
	{
		if (t->seats[i].must_eat != 0)
			return ;
	}
	t->finish_dinner = true;
}
