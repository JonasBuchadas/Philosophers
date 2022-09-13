#include "philo_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}
