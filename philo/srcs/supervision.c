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
static void	all_philo_eated(t_table *t);

void	*supervise_eat(void *arg)
{
	t_table	*t;

	t = (t_table *)arg;
	while (!is_finished(t))
	{
		all_philo_eated(t);
		usleep(1000);
	}
	return (NULL);
}

void	*supervise_death(void *arg)
{
	t_table		*t;
	int			i;
	long long	time_eated;

	t = (t_table *)arg;
	while (!is_finished(t))
	{
		i = -1;
		while (++i < t->philo_number)
		{
			pthread_mutex_lock(&t->time);
			time_eated = t->seats[i].time_eated;
			pthread_mutex_unlock(&t->time);
			if (timestamp(t->time_started) - time_eated > t->time_to_die)
			{
				message(t->seats + i, DEATH);
				pthread_mutex_lock(&t->death);
				t->thread_dead = true;
				pthread_mutex_unlock(&t->death);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}

static void	all_philo_eated(t_table *t)
{
	int	i;
	int must_eat;

	i = -1;
	while (++i < t->philo_number)
	{
		pthread_mutex_lock(&t->all_eat);
		must_eat = t->seats[i].must_eat;
		pthread_mutex_unlock(&t->all_eat);
		if (must_eat != 0)
			return ;
	}
	pthread_mutex_lock(&t->all_eat);
	t->finish_dinner = true;
	pthread_mutex_unlock(&t->all_eat);
}

static bool	is_finished(t_table *t)
{
	bool	finish_dinner;
	bool	philo_died;

	pthread_mutex_lock(&t->death);
	philo_died = t->thread_dead;
	pthread_mutex_unlock(&t->death);
	pthread_mutex_lock(&t->all_eat);
	finish_dinner = t->finish_dinner;
	pthread_mutex_unlock(&t->all_eat);
	if ((finish_dinner || philo_died))
		return (true);
	return (false);
}
