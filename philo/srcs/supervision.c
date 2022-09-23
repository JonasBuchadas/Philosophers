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

static bool	is_finished(t_table *t);
static bool	all_philo_eated(t_table *t);
static void	kill_philo(t_table *t, int i);

void	*supervise_eat(void *arg)
{
	t_table	*t;

	t = (t_table *)arg;
	while (!is_finished(t))
	{
		if (all_philo_eated(t))
			return (NULL);
	}
	return (NULL);
}

void	*supervise_death(void *arg)
{
	t_table		*t;
	int			i;

	t = (t_table *)arg;
	while (!is_finished(t))
	{
		i = -1;
		while (++i < t->philo_number)
		{
			pthread_mutex_lock(&t->time);
			if (timestamp(t->time_started) - t->seats[i].time_eated
				> t->time_to_die)
			{
				pthread_mutex_unlock(&t->time);
				kill_philo(t, i);
				return (NULL);
			}
			pthread_mutex_unlock(&t->time);
		}
	}
	return (NULL);
}

static void	kill_philo(t_table *t, int i)
{
	if (!is_finished(t))
	{
		pthread_mutex_lock(&t->message);
		printf("%lld %d died\n",
			timestamp(t->time_started), i + 1);
		pthread_mutex_unlock(&t->message);
		pthread_mutex_lock(&t->death);
		t->thread_dead = true;
		pthread_mutex_unlock(&t->death);
	}
}

static bool	all_philo_eated(t_table *t)
{
	int	i;
	int	must_eat;

	i = -1;
	while (++i < t->philo_number)
	{
		pthread_mutex_lock(&t->all_eat);
		must_eat = t->seats[i].must_eat;
		pthread_mutex_unlock(&t->all_eat);
		if (must_eat != 0)
			return (false);
	}
	pthread_mutex_lock(&t->all_eat);
	t->finish_dinner = true;
	pthread_mutex_unlock(&t->all_eat);
	return (true);
}

static bool	is_finished(t_table *t)
{
	bool	finish_dinner;
	bool	philo_died;

	pthread_mutex_lock(&t->all_eat);
	finish_dinner = t->finish_dinner;
	pthread_mutex_unlock(&t->all_eat);
	pthread_mutex_lock(&t->death);
	philo_died = t->thread_dead;
	pthread_mutex_unlock(&t->death);
	if ((finish_dinner || philo_died))
		return (true);
	return (false);
}
