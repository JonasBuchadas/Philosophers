/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrange_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:26:16 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 17:26:17 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	arrange_seats(t_table *t);

void	arrange_table(t_table *t)
{
	arrange_seats(t);
}

static void	arrange_seats(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_number)
	{
		t->seats[i].id = i + 1;
		t->seats[i].forks = &t->forks;
		t->seats[i].message = &t->message;
		t->seats[i].time = &t->time;
		t->seats[i].death = &t->death;
		t->seats[i].all_eat = &t->all_eat;
		t->seats[i].time_to_die = t->time_to_die;
		t->seats[i].time_to_eat = t->time_to_eat;
		t->seats[i].time_eated = 0;
		t->seats[i].time_to_sleep = t->time_to_sleep;
		t->seats[i].dead = &t->thread_dead;
		t->seats[i].finish_dinner = &t->finish_dinner;
		if (t->opt_arg == true)
			t->seats[i].must_eat = t->must_eat;
		else
			t->seats[i].must_eat = -1;
	}
}
