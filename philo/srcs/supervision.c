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
