#include "philo.h"

static int	init_philo(t_table *table, char **argv);
static int	set_table(t_table *t);
static int	start_dinner(t_table *t);
static int	create_supervision_threads(t_table *t);

int	main(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		exit_philo(table, MALLOC);
	if (argc < 5 || argc > 6)
		return (exit_philo(table, NUM_OF_ARGS));
	if (init_philo(table, argv) != 0)
		return (exit_philo(table, ARGS));
	if (set_table(table) != 0)
		return (exit_philo(table, MALLOC));
	if (start_dinner(table) != 0)
		return (exit_message(table, THREAD, "Error while making thread"));
	return (exit_philo(table, SUCCESS));
}

static int	init_philo(t_table *t, char **argv)
{
	t->philo_number = ft_atoi(argv[1]);
	t->time_to_die = ft_atoui(argv[2]);
	t->time_to_eat = ft_atoui(argv[3]);
	t->time_to_sleep = ft_atoui(argv[4]);
	t->finish_dinner = false;
	t->thread_dead = false;
	if (argv[5])
	{
		t->must_eat = ft_atoi(argv[5]);
		t->opt_arg = true;
	}
	else
	{
		t->must_eat = 0;
		t->opt_arg = false;
	}
	if (t->philo_number < 1)
		return (1);
	if (t->time_to_die == 0 || t->time_to_eat == 0
		|| t->time_to_sleep == 0)
		return (1);
	if (t->must_eat < 0)
		return (1);
	return (0);
}

static int	set_table(t_table *t)
{
	int	i;

	t->forks = (t_mutex *)malloc(sizeof(t_mutex) * t->philo_number);
	if (!t->forks)
		return (MALLOC);
	t->f_taken = (bool *)malloc(sizeof(bool) * t->philo_number);
	if (!t->f_taken)
		return (MALLOC);
	memset(t->f_taken, false, sizeof(bool) * t->philo_number);
	t->seats = (t_seat *)malloc(sizeof(t_seat) * t->philo_number);
	if (!t->seats)
		return (MALLOC);
	i = -1;
	while (++i < t->philo_number)
		pthread_mutex_init(t->forks + i, NULL);
	pthread_mutex_init(&t->message, NULL);
	arrange_table(t);
	return (0);
}

static int	start_dinner(t_table *t)
{
	int			i;

	t->time_started = get_current_time(0);
	i = -1;
	while (++i < t->philo_number)
	{
		t->seats[i].time_started = t->time_started;
		if (pthread_create(&t->seats[i].philo, NULL,
				&dinner, &t->seats[i]) != 0)
			return (exit_message(t, THREAD, "Error while making thread"));
		usleep(1000);
	}
	if (create_supervision_threads(t) != 0)
		return (exit_message(t, THREAD, "Error while making thread"));
	i = -1;
	while (++i < t->philo_number)
	{
		if (pthread_join(t->seats[i].philo, NULL) != 0)
			return (exit_message(t, THREAD, "Error while waiting thread"));
	}
	return (0);
}

static int create_supervision_threads(t_table *t)
{
	pthread_t supervisor;
	pthread_t death;

	if (pthread_create(&supervisor, NULL,
					   &supervise_dinner, t) != 0)
		return (exit_message(t, THREAD, "Error while making thread"));
	if (pthread_create(&death, NULL,
					   &supervise_death, t) != 0)
		return (exit_message(t, THREAD, "Error while making thread"));
	pthread_detach(supervisor);
	pthread_detach(death);
	return (SUCCESS);
}
