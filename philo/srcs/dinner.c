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

#include "philo.h"

static void	eating(t_seat *seat);
static void	sleeping(t_seat *seat);
static void	thinking(t_seat *seat);
static void	take_forks(t_seat *seat);

void	*dinner(void *arg)
{
	t_seat	*seat;

	seat = (t_seat *)arg;
	if (seat->id % 2)
	{
		thinking(seat);
		usleep(15000);
	}
	while (!end_dinner(seat))
	{
		eating(seat);
		sleeping(seat);
		thinking(seat);
	}
	return (NULL);
}

static void	eating(t_seat *seat)
{
	if (seat->left_fork == seat->right_fork)
		philo_sleep(seat, seat->time_to_die);
	if (!end_dinner(seat))
	{
		take_forks(seat);
		pthread_mutex_lock(seat->all_eat);
		if (seat->must_eat > 0)
			seat->must_eat--;
		pthread_mutex_unlock(seat->all_eat);
		message(seat, EAT);
		pthread_mutex_lock(seat->time);
		seat->time_eated = timestamp(seat->time_started);
		pthread_mutex_unlock(seat->time);
		philo_sleep(seat, seat->time_to_eat);
		pthread_mutex_unlock(seat->left_fork);
		pthread_mutex_unlock(seat->right_fork);
	}
}

static void	take_forks(t_seat *seat)
{
	if (seat->id % 2 == 0)
	{
		pthread_mutex_lock(seat->right_fork);
		pthread_mutex_lock(seat->left_fork);
	}
	else
	{
		pthread_mutex_lock(seat->left_fork);
		pthread_mutex_lock(seat->right_fork);
	}
}

static void	sleeping(t_seat *seat)
{
	if (!end_dinner(seat))
	{
		message(seat, SLEEP);
		philo_sleep(seat, seat->time_to_sleep);
	}
}

static void	thinking(t_seat *seat)
{
	if (!end_dinner(seat))
		message(seat, THINKING);
}
