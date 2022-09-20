/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:25:37 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 17:48:58 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	t->time_to_die = ft_atoi(argv[2]);
	t->time_to_eat = ft_atoi(argv[3]);
	t->time_to_sleep = ft_atoi(argv[4]);
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
	if (t->philo_number < 1 || t->time_to_die < 1 || t->time_to_eat < 1
		|| t->time_to_sleep < 1)
		return (1);
	if (t->must_eat < 0)
		return (1);
	return (SUCCESS);
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
	return (SUCCESS);
}

static int	start_dinner(t_table *t)
{
	int			i;

	t->time_started = timestamp(0);
	i = -1;
	while (++i < t->philo_number)
	{
		t->seats[i].time_started = timestamp(0);
		if (pthread_create(&t->seats[i].philo, NULL,
				&dinner, &t->seats[i]) != 0)
			return (THREAD);
	}
	if (create_supervision_threads(t) != 0)
		return (THREAD);
	i = -1;
	while (++i < t->philo_number)
	{
		if (pthread_join(t->seats[i].philo, NULL) != 0)
			return (THREAD);
	}
	return (SUCCESS);
}

static int	create_supervision_threads(t_table *t)
{
	pthread_t	death_supervisor;
	pthread_t	eat_supervisor;

	if (pthread_create(&death_supervisor, NULL,
			&supervise_death, t) != 0)
		return (THREAD);
	if (t->opt_arg == true)
	{
		if (pthread_create(&eat_supervisor, NULL,
				&supervise_eat, t) != 0)
			return (THREAD);
		pthread_detach(eat_supervisor);
	}
	pthread_detach(death_supervisor);
	return (SUCCESS);
}
