/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:25:48 by jocaetan          #+#    #+#             */
/*   Updated: 2022/09/18 17:25:49 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			maxlen;
	unsigned char	c1;
	unsigned char	c2;

	if (ft_strlen(s1) > ft_strlen(s2))
		maxlen = ft_strlen(s1);
	else
		maxlen = ft_strlen(s2);
	i = -1;
	while (++i < n && i < maxlen)
	{
		c1 = s1[i];
		c2 = s2[i];
		if ((c1 != c2))
			return (c1 - c2);
	}
	return (0);
}
