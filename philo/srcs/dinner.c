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

static void	sleeping(t_seat *seat);
static void	thinking(t_seat *seat);

void	*dinner(void *arg)
{
	t_seat	*seat;

	seat = (t_seat *)arg;
	seat->time_started = timestamp(0);
	while (!(*seat->finish_dinner || *seat->dead))
	{
		eating(seat);
		sleeping(seat);
		thinking(seat);
	}
	return (NULL);
}

static void	sleeping(t_seat *seat)
{
	if (!(*seat->finish_dinner || *seat->dead))
	{
		message(seat, SLEEP);
		usleep(seat->time_to_sleep * 1000);
	}
}

static void	thinking(t_seat *seat)
{
	if (!(*seat->finish_dinner || *seat->dead))
		message(seat, THINKING);
}
