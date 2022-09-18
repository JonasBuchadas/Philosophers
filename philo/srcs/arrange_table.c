#include "philo.h"

static void	arrange_seats(t_table *t);
static void	arrange_forks(t_table *t);

void	arrange_table(t_table *t)
{
	arrange_seats(t);
	arrange_forks(t);
}

static void	arrange_seats(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_number)
	{
		t->seats[i].id = i + 1;
		t->seats[i].forks_taken = false;
		t->seats[i].eat_allow = true;
		t->seats[i].message = &t->message;
		t->seats[i].time_to_die = t->time_to_die;
		t->seats[i].time_to_eat = t->time_to_eat;
		t->seats[i].time_eated = 0;
		t->seats[i].time_to_sleep = t->time_to_sleep;
		t->seats[i].dead = &t->thread_dead;
		t->seats[i].finish_dinner = &t->finish_dinner;
		if (t->opt_arg == true)
			t->seats[i].must_eat = t->must_eat;
		else
			t->seats[i].must_eat = -1;
	}
}

static void	arrange_forks(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_number - 1)
	{
		t->seats[i].left_fork = &t->forks[i];
		t->seats[i].right_fork = &t->forks[i + 1];
	}
	t->seats[i].left_fork = &t->forks[i];
	t->seats[i].right_fork = &t->forks[0];
	i = -1;
	while (++i < t->philo_number - 1)
	{
		t->seats[i].l_f_taken = &t->f_taken[i];
		t->seats[i].r_f_taken = &t->f_taken[i + 1];
	}
	t->seats[i].l_f_taken = &t->f_taken[i];
	t->seats[i].r_f_taken = &t->f_taken[0];
}
