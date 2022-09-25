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

static void	take_forks(t_seat *seat);
static void	eating(t_seat *seat);
static void	sleeping(t_seat *seat);
static void	thinking(t_seat *seat);

int	dinner(t_seat *seat)
{
	if (seat->id % 2)
	{
		thinking(seat);
		usleep(15000);
	}
	while (!end_dinner(seat))
	{
		take_forks(seat);
		eating(seat);
		sem_post(*seat->forks);
		sem_post(*seat->forks);
		sleeping(seat);
		thinking(seat);
	}
	return (SUCCESS);
}

static void	eating(t_seat *seat)
{
	if (!end_dinner(seat))
	{
		sem_wait(*seat->message);
		printf("%lld %d is eating\n",
			timestamp(seat->time_started), seat->id);
		sem_post(*seat->message);
		sem_wait(*seat->all_eat);
		if (seat->must_eat > 0)
			seat->must_eat--;
		sem_post(*seat->all_eat);
		sem_wait(*seat->time);
		seat->time_eated = timestamp(seat->time_started);
		sem_post(*seat->time);
		philo_sleep(seat, seat->time_to_eat);
	}
}

static void	take_forks(t_seat *seat)
{
	if (!end_dinner(seat))
	{
		sem_wait(*seat->forks);
		sem_wait(*seat->forks);
	}
	if (!end_dinner(seat))
	{
		sem_wait(*seat->message);
		printf("%lld %d has taken a fork\n",
			timestamp(seat->time_started), seat->id);
		printf("%lld %d has taken a fork\n",
			timestamp(seat->time_started), seat->id);
		sem_post(*seat->message);
	}
}

static void	sleeping(t_seat *seat)
{
	if (!end_dinner(seat))
	{
		sem_wait(*seat->message);
		printf("%lld %d is sleeping\n",
			timestamp(seat->time_started), seat->id);
		sem_post(*seat->message);
		philo_sleep(seat, seat->time_to_sleep);
	}
}
static void	thinking(t_seat *seat)
{
	if (!end_dinner(seat))
	{
		sem_wait(*seat->message);
		printf("%lld %d is thinking\n",
			timestamp(seat->time_started), seat->id);
		sem_post(*seat->message);
	}
}

