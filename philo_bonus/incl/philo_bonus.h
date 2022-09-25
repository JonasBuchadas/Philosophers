/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:25:44 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 17:37:18 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/wait.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define LEFT_FORK 0
# define RIGHT_FORK 1
# define PHILO_PROCESS 0
# define SUCCESS 0
# define MALLOC 1
# define NUM_OF_ARGS 2
# define ARGS 3
# define PROCESS 4
# define THREAD 5

# define FORK_SEM "/forks"
# define MESSAGE_SEM "/message"

typedef pthread_mutex_t	t_mutex;

typedef enum s_status
{
	THINKING,
	FORK,
	EAT,
	SLEEP,
	DEATH
}	t_status;

typedef struct s_seat
{
	pthread_t	philo;
	pid_t		pid;
	int			id;
	long long	time_started;
	long long	time_eated;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	bool		*dead;
	bool		*finish_dinner;
	sem_t		**forks;
	sem_t		**message;
}	t_seat;

typedef struct s_table
{
	int			philo_number;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	long long	time_started;
	int			must_eat;
	bool		opt_arg;
	bool		thread_dead;
	bool		finish_dinner;
	t_seat		*seats;
	sem_t		*forks;
	sem_t		*message;
}	t_table;

int				exit_philo(t_table *table, int error_code);
int				exit_message(t_table *table, int error_code, char *msg);
void			*dinner(void *arg);
void			message(t_seat *seat, int status);
void			philo_sleep(t_seat *seat, long long msecs);
long long		timestamp(long long start_time);
void			arrange_table(t_table *t);
void			*supervise_eat(void *arg);
void			*supervise_death(void *arg);
int				ft_atoi(const char *str);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);

#endif
