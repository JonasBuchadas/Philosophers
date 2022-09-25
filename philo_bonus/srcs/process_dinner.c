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

static int	create_supervision_threads(t_seat *seat);

int	process_dinner(t_seat *seat)
{
	seat->time_started = timestamp(0);
	seat->time_eated = timestamp(seat->time_started);
	if (create_supervision_threads(seat) != 0)
		return (THREAD);
	dinner(seat);
	if (pthread_join(seat->death_supervisor, NULL) != 0)
		return (THREAD);
	if (pthread_join(seat->eat_supervisor, NULL) != 0)
		return (THREAD);
	return (SUCCESS);
}

static int	create_supervision_threads(t_seat *seat)
{
	if (pthread_create(&seat->death_supervisor, NULL,
			&supervise_death, seat) != 0)
		return (THREAD);
	if (!seat->must_eat)
	{
		if (pthread_create(&seat->eat_supervisor, NULL,
				&supervise_eat, seat) != 0)
			return (THREAD);
	}
	return (SUCCESS);
}
