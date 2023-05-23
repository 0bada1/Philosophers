/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:03:23 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/23 14:09:14 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time2(t_philo *philo)
{
	gettimeofday(&philo->node->tv, NULL);
	return ((philo->node->tv.tv_sec * 1000LL)
		+ (philo->node->tv.tv_usec / 1000LL) - philo->node->starting_time);
}

int	ft_usleep(t_philo *philo, size_t time_of_action, size_t time_to_usleep)
{
	size_t	time;

	if (!philo || !philo->node || time_to_usleep == 0)
		return (1);
	time = allocate_time(philo);
	while (time - time_of_action <= time_to_usleep)
	{
		usleep(50);
		time = allocate_time(philo);
	}
	return (0);
}

int	one_philo(t_philo *philo)
{
	size_t	time;

	time = get_time2(philo);
	if (philo->node->num_of_philos == 1)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		pthread_mutex_lock(&philo->node->print_lock);
		printf(GREEN"%li Philo 1 has picked up a fork\n"WHITE, time);
		pthread_mutex_unlock(&philo->node->print_lock);
		pthread_mutex_unlock(&philo->right_fork->fork);
		ft_usleep(philo, time, philo->node->time_to_die - 1);
		time = get_time2(philo);
		pthread_mutex_lock(&philo->node->print_lock);
		printf(RED"%li Philo 1 has died\n"WHITE, time);
		pthread_mutex_unlock(&philo->node->print_lock);
		return (TRUE);
	}
	return (FALSE);
}

void	eat_order(t_philo *philo)
{
	if (philo->node->num_of_philos % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			philo_eat(philo);
		else
			ft_usleep(philo, 0, philo->node->time_to_eat);
	}
	else if (philo->node->num_of_philos % 2 == 1)
	{
		if (philo->philo_id % 2 == 1)
			philo_eat(philo);
		else
			ft_usleep(philo, 0, philo->node->time_to_eat);
	}
}

void	call_life_and_mutex(t_philo *philo)
{
	philo_life(philo);
	pthread_mutex_lock(&philo->node->simulation_lock);
}
