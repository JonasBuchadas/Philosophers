/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
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

int	main(int argc, char **argv)
{
	t_table	*table;
	int		error;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		exit_philo(table, MALLOC);
	if (argc < 5 || argc > 6)
		return (exit_philo(table, NUM_OF_ARGS));
	error = init_philo(table, argv);
	if (error != 0)
		return (exit_philo(table, error));
	error = set_table(table);
	if (error != 0)
		return (exit_philo(table, error));
	error = start_dinner(table);
	if (error != 0)
		return (exit_philo(table, error));
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
		|| t->time_to_sleep < 1 || t->must_eat < 0)
		return (1);
	return (SUCCESS);
}

static int	set_table(t_table *t)
{
	sem_unlink(FORK_SEM);
	sem_unlink(MESSAGE_SEM);
	sem_unlink(TIME_SEM);
	sem_unlink(DEATH_SEM);
	sem_unlink(ALL_EAT_SEM);
	t->forks = sem_open(FORK_SEM, O_CREAT, S_IRWXU, t->philo_number);
	if (!t->forks)
		return (MALLOC);
	t->message = sem_open(MESSAGE_SEM, O_CREAT, S_IRWXU, 1);
	if (!t->message)
		return (MALLOC);
	t->message = sem_open(TIME_SEM, O_CREAT, S_IRWXU, 1);
	if (!t->message)
		return (MALLOC);
	t->message = sem_open(DEATH_SEM, O_CREAT, S_IRWXU, 1);
	if (!t->message)
		return (MALLOC);
	t->message = sem_open(ALL_EAT_SEM, O_CREAT, S_IRWXU, 1);
	if (!t->message)
		return (MALLOC);
	t->seats = (t_seat *)malloc(sizeof(t_seat) * t->philo_number);
	if (!t->seats)
		return (MALLOC);
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
		if (t->seats[i].pid == -1)
			return (PROCESS);
		if (t->seats[i].pid == PHILO_PROCESS)
			process_dinner(t->seats + i);
	}
	return (SUCCESS);
}
