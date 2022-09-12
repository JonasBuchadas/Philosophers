#include "philo.h"

static void	is_finished(t_table *t);
static void	someone_died(t_table *t);

void	*supervise_dinner(void *arg)
{
	t_table	*t;

	t = (t_table *)arg;
	while (!(t->finish_dinner || t->thread_dead))
	{
		if (t->opt_arg == true)
			is_finished(t);
		someone_died(t);
	}
	return (NULL);
}

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

static void	someone_died(t_table *t)
{
	int		i;
	t_seat	*s;

	i = -1;
	while (++i < t->philo_number)
	{
		s = t->seats + i;
		if (get_current_time(s->time_started) - s->time_eated > s->time_to_die)
		{
			message(s, DEATH);
			t->thread_dead = true;
		}
		usleep(1000);
	}
}
