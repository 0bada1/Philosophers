/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:04:01 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/23 14:32:47 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			j;
	size_t		value;

	i = 0;
	j = 1;
	value = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			j *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - 48);
		if (value > 2147483647)
			return (-1);
		i++;
	}
	if ((value > (size_t)2147483647 && j == 1)
		|| (value > (size_t)2147483648 && j == -1))
		return (-1);
	return (value * j);
}

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	int			bzero;
	char		*char_s;

	i = 0;
	bzero = 0;
	char_s = (char *)s;
	while (i < n)
	{
		char_s[i] = bzero;
		i++;
	}
	s = char_s;
	return ;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && (nmemb > SIZE_MAX / size))
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

t_philo	*philo_think_v1(t_philo *philo)
{
	philo->action = 'T';
	philo_life(philo);
	return (philo);
}
