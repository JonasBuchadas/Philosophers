/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:26:04 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 17:26:05 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int	readnumbers(const char *str, int i, int signal);
static int			check_overflow(const char *str, int i, int signal);
static int			check_signal(char c);
static int			ft_isspace(int c);

unsigned int	ft_atoui(const char *str)
{
	int	i;
	int	signal_int;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	signal_int = check_signal(str[i]);
	if (signal_int != 0)
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		return (readnumbers(str, i, signal_int));
	return (0);
}

static unsigned int	readnumbers(const char *str, int i, int signal)
{
	unsigned int	result;

	result = check_overflow(str, i, signal);
	if (result != 0)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result);
}

static int	check_signal(char c)
{
	if (c == '+')
		return (1);
	if (c == '-')
		return (-1);
	return (0);
}

static int	check_overflow(const char *str, int i, int signal)
{
	int		len;
	int		index;
	char	*max;

	len = 0;
	index = i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		len++;
		i++;
	}
	i = index;
	max = "4294967295";
	if (len > 10 || signal < 0)
		return (1);
	else if (len == 10 && signal >= 0 && ft_strncmp(&str[i], max, 10) > 0)
		return (1);
	else if (len < 10)
		return (0);
	return (0);
}

static int	ft_isspace(int c)
{
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	if (c == ' ')
		return (1);
	else
		return (0);
}
