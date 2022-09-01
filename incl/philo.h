#ifndef PHILO_H
# define PHILO_H

# include <sys/wait.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define SUCCESS 0
# define MALLOC 1
# define NUM_OF_ARGS 2
# define ARGS 3
# define THREAD 4

#define mutex_t pthread_mutex_t

typedef struct s_seat
{
	pthread_t	philosopher;
	int			id;
	int			must_eat;
	mutex_t		*left_fork;
	mutex_t		*right_fork;
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
}	t_table;

int				exit_philo(t_table *table, int error_code);
int				exit_message(t_table *table, int error_code, char *msg);
void			*dinner();

unsigned int	ft_atoui(const char *str);
int				ft_atoi(const char *str);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);

#endif
