/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 03:04:35 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/11 20:39:37 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	allocate_time(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->node->time_lock);
	time = (size_t)get_time2(philo);
	pthread_mutex_unlock(&philo->node->time_lock);
	return (time);
}

t_philo	*philo_eat_v1(t_philo *philo)
{
	philo->right_fork->state = NOT_AVAILABLE;
	philo->left_fork->state = NOT_AVAILABLE;
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	philo_life(philo);
	return (philo);
}

t_philo	*philo_eat_v2(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->node->simulation_lock);
	if (philo->node->simulation_status == TRUE)
	{
		pthread_mutex_unlock(&philo->node->simulation_lock);
		time = allocate_time(philo);
		pthread_mutex_lock(&philo->node->print_lock);
		if (philo->node->simulation_status == TRUE)
		{
			printf(GREEN"%li Philo %i has picked up a fork\n"
				WHITE, time, philo->philo_id + 1);
			printf(GREEN"%li Philo %i has picked up a fork\n"
				WHITE, time, philo->philo_id + 1);
		}
		pthread_mutex_unlock(&philo->node->print_lock);
	}
	else
		pthread_mutex_unlock(&philo->node->simulation_lock);
	return (philo);
}

t_philo	*philo_life_v1(t_philo *philo, size_t time)
{
	pthread_mutex_lock(&philo->life_mutex);
	if (philo->life <= 0)
	{
		pthread_mutex_unlock(&philo->life_mutex);
		pthread_mutex_lock(&philo->node->simulation_lock);
		pthread_mutex_lock(&philo->node->print_lock);
		if (philo->node->simulation_status == TRUE)
			printf(RED"%li Philo %i has died\n"
				WHITE, time, philo->philo_id + 1);
		philo->node->simulation_status = FALSE;
		pthread_mutex_unlock(&philo->node->print_lock);
		pthread_mutex_unlock(&philo->node->simulation_lock);
	}
	else
		pthread_mutex_unlock(&philo->life_mutex);
	return (philo);
}

t_philo	*philo_life_v2(t_philo *philo)
{
	pthread_mutex_lock(&philo->node->simulation_lock);
	pthread_mutex_lock(&philo->node->print_lock);
	if (philo->node->philos_done_eating >= (philo->node->num_of_philos
			* philo->node->number_of_times_to_eat))
	{
		philo->node->simulation_status = FALSE;
		pthread_mutex_unlock(&philo->node->print_lock);
		pthread_mutex_unlock(&philo->node->simulation_lock);
		return (philo);
	}
	pthread_mutex_unlock(&philo->node->print_lock);
	pthread_mutex_unlock(&philo->node->simulation_lock);
	return (philo);
}
