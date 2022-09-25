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

#include "philo_bonus.h"

static bool is_finished(t_seat *s);
static void	kill_philo(t_seat *s);
static bool all_eated(t_seat *seat);

void	*supervise_eat(void *arg)
{
	t_seat	*seat;

	seat = (t_seat *)arg;
	while (!is_finished(seat))
	{
		if (all_eated(seat))
			return (NULL);
	}
	return (NULL);
}

void	*supervise_death(void *arg)
{
	t_seat	*s;

	s = (t_seat *)arg;
	while (!is_finished(s))
	{
		sem_wait(*s->time);
		if (timestamp(s->time_started) - s->time_eated > s->time_to_die)
		{
			sem_post(*s->time);
			kill_philo(s);
			return (NULL);
		}
		sem_post(*s->time);
	}
	return (NULL);
}

static void	kill_philo(t_seat *s)
{
	if (!is_finished(s))
	{
		sem_wait(*s->message);
		printf("%lld %d died\n",
			timestamp(s->time_started), s->id);
		sem_post(*s->message);
		sem_wait(*s->death);
		*s->dead = true;
		sem_post(*s->death);
	}
}

static bool all_eated(t_seat *seat)
{
	int must_eat;

	sem_wait(*seat->all_eat);
	must_eat = seat->must_eat;
	sem_post(*seat->all_eat);
	if (must_eat != 0)
		return (false);
	sem_wait(*seat->all_eat);
	*seat->finish_dinner = true;
	sem_post(*seat->all_eat);
	return (true);
}

static bool is_finished(t_seat *s)
{
	bool finish_dinner;
	bool philo_died;

	sem_wait(*s->all_eat);
	finish_dinner = s->finish_dinner;
	sem_post(*s->all_eat);
	sem_wait(*s->death);
	philo_died = *s->dead;
	sem_post(*s->death);
	if ((finish_dinner || philo_died))
		return (true);
	return (false);
}
