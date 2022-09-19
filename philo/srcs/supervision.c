/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:25:28 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 17:25:31 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_finished(t_table *t);
static void	give_priorities(t_seat *left_philo, t_seat *right_philo);

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

void	*supervise_priority(void *arg)
{
	t_table		*t;
	int			i;

	t = (t_table *)arg;
	while (!(t->finish_dinner || t->thread_dead))
	{
		i = -1;
		while (++i < t->philo_number - 1)
			give_priorities(t->seats + i, t->seats + (i + 1));
		give_priorities(t->seats + i, t->seats);
	}
	return (NULL);
}

static void	give_priorities(t_seat *left_philo, t_seat *right_philo)
{
	if (left_philo->time_eated > right_philo->time_eated)
	{
		left_philo->eat_allow = false;
		right_philo->eat_allow = true;
	}
	else if (left_philo->time_eated == right_philo->time_eated)
	{
		left_philo->eat_allow = true;
		right_philo->eat_allow = true;
	}
	else
	{
		left_philo->eat_allow = true;
		right_philo->eat_allow = false;
	}
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
