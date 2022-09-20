/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:26:13 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 17:26:14 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eating(t_seat *seat);
static void	sleeping(t_seat *seat);
static void	thinking(t_seat *seat);

void	*dinner(void *arg)
{
	t_seat	*seat;

	seat = (t_seat *)arg;
	if (seat->id % 2)
	{
		thinking(seat);
		usleep(15000);
	}
	while (!(*seat->finish_dinner || *seat->dead))
	{
		eating(seat);
		sleeping(seat);
		thinking(seat);
	}
	return (NULL);
}

static void	eating(t_seat *seat)
{
	if (!(*seat->finish_dinner || *seat->dead))
	{
		sem_wait(*seat->forks);
		sem_wait(*seat->forks);
		if (seat->must_eat > 0)
			seat->must_eat--;
		message(seat, EAT);
		seat->time_eated = timestamp(seat->time_started);
		philo_sleep(seat, seat->time_to_eat);
		sem_post(*seat->forks);
		sem_post(*seat->forks);
	}
}

static void	sleeping(t_seat *seat)
{
	if (!(*seat->finish_dinner || *seat->dead))
	{
		message(seat, SLEEP);
		philo_sleep(seat, seat->time_to_sleep);
	}
}

static void	thinking(t_seat *seat)
{
	if (!(*seat->finish_dinner || *seat->dead))
		message(seat, THINKING);
}
