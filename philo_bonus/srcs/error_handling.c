/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:26:10 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 17:26:11 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int			exit_philo(t_table *table, int error_code);
int			exit_message(t_table *table, int error_code, char *msg);
static void	free_table(t_table *table);
static void	incorrect_arg(t_table *t);

int	exit_philo(t_table *table, int error_code)
{
	if (error_code == MALLOC)
		ft_putendl_fd("Error allocating memory.", 2);
	if (error_code == NUM_OF_ARGS)
	{
		ft_putendl_fd("Incorrect arguments given.", 2);
		ft_putstr_fd("USAGE: ./philo [number_of_philosophers]", 2);
		ft_putstr_fd(" [time_to_die]", 2);
		ft_putstr_fd(" [time_to_eat]", 2);
		ft_putstr_fd(" [time_to_sleep]", 2);
		ft_putstr_fd(" [number_of_times_each_philosopher_must_eat]", 2);
		ft_putstr_fd(" (optional argument)\n", 2);
	}
	if (error_code == ARGS)
		incorrect_arg(table);
	free_table(table);
	return (error_code);
}

int	exit_message(t_table *table, int error_code, char *msg)
{
	ft_putendl_fd(msg, 2);
	free_table(table);
	return (error_code);
}

static void	free_table(t_table *table)
{
	if (table != NULL)
	{
		sem_close(table->forks);
		sem_close(table->message);
		sem_unlink(FORK_SEM);
		sem_unlink(MESSAGE_SEM);
		if (table->seats)
			free(table->seats);
		free(table);
	}
	return ;
}

static void	incorrect_arg(t_table *t)
{
	if (t->philo_number < 1)
	{
		ft_putstr_fd("Argument [number_of_philosophers] ", 2);
		ft_putendl_fd("must be a positive int.", 2);
	}
	if (t->time_to_die < 1)
		ft_putendl_fd("Argument [time_to_die] must be positive int.", 2);
	if (t->time_to_eat < 1)
		ft_putendl_fd("Argument [time_to_eat] must be positive int.", 2);
	if (t->time_to_sleep < 1)
		ft_putendl_fd("Argument [time_to_sleep] must be positive int.", 2);
	if (t->opt_arg && t->must_eat < 1)
	{
		ft_putstr_fd("Argument [number_of_times_", 2);
		ft_putstr_fd("each_philosopher_must_eat] ", 2);
		ft_putendl_fd("must be a positive int", 2);
	}
	return ;
}
