/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:25:44 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 17:37:18 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	time_diff(long long present, long long past);

long long	timestamp(long long start_time)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL + tv.tv_usec / 1000) - start_time);
}

static long long	time_diff(long long present, long long past)
{
	return (present - past);
}

void	philo_sleep(t_seat *seat, long long msecs)
{
	long long	start;

	start = timestamp(seat->time_started);
	while (!end_dinner(seat))
	{
		if (time_diff(timestamp(seat->time_started), start) >= msecs)
			break ;
		usleep(50);
	}
}
