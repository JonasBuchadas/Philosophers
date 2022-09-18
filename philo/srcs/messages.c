/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:25:41 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 17:25:42 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_seat *seat, int status)
{
	pthread_mutex_lock(seat->message);
	if (!*seat->dead)
	{
		if (status == THINKING)
			printf("%lld %d is thinking\n",
				timestamp(seat->time_started), seat->id);
		if (status == FORK)
			printf("%lld %d has taken a fork\n",
				timestamp(seat->time_started), seat->id);
		if (status == EAT)
			printf("%lld %d is eating\n",
				timestamp(seat->time_started), seat->id);
		if (status == SLEEP)
			printf("%lld %d is sleeping\n",
				timestamp(seat->time_started), seat->id);
		if (status == DEATH)
			printf("%lld %d died\n",
				timestamp(seat->time_started), seat->id);
	}
	pthread_mutex_unlock(seat->message);
}
