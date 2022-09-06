#ifndef PHILO_H
# define PHILO_H

# include <sys/wait.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define LEFT_FORK 0
# define RIGHT_FORK 1
# define SUCCESS 0
# define MALLOC 1
# define NUM_OF_ARGS 2
# define ARGS 3
# define THREAD 4

#define mutex_t pthread_mutex_t

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
	int			id;
	long long	time_started;
	int			must_eat;
	mutex_t		*left_fork;
	mutex_t		*right_fork;
	bool		*l_f_taken;
	bool		*r_f_taken;
	bool		forks_taken;
	mutex_t		*message;
}	t_seat;

typedef struct s_table
{
	int				philo_number;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				must_eat_number;
	bool			opt_arg;
	t_seat			*seats;
	mutex_t			*forks;
	mutex_t			message;
	bool			*f_taken;
}	t_table;

int				exit_philo(t_table *table, int error_code);
int				exit_message(t_table *table, int error_code, char *msg);
void			*dinner();
void			message(t_seat *seat, int status);
long long 		get_current_time(long long start_time);
void 			arrange_table(t_table *t);
unsigned int	ft_atoui(const char *str);
int				ft_atoi(const char *str);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);

#endif
