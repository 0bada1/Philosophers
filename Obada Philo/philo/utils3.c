/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 03:04:35 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/15 20:39:37 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*philo_eat_v3(t_philo *philo)
{
    size_t  time;

	philo->action = 'E';
	pthread_mutex_lock(&philo->life_mutex);
	philo->life = philo->node->time_to_die;
	pthread_mutex_unlock(&philo->life_mutex);
    time = allocate_time(philo);
	philo->time_of_eating = time;
	philo_life(philo);
	pthread_mutex_lock(&philo->node->simulation_lock);
	if (philo->node->simulation_status == TRUE)
	{
		pthread_mutex_unlock(&philo->node->simulation_lock);
		pthread_mutex_lock(&philo->node->print_lock);
		if (philo->node->simulation_status == TRUE)
		{
			printf(GREEN"%li Philo %i is eating\n"
				WHITE, time, philo->philo_id + 1);
			philo->node->philos_done_eating++;
		}
		pthread_mutex_unlock(&philo->node->print_lock);
	}
	else
		pthread_mutex_unlock(&philo->node->simulation_lock);
	return (philo);
}

int lock_forks(t_philo *philo)
{
    if (!philo)
        return (-1);
    if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		pthread_mutex_lock(&philo->left_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		pthread_mutex_lock(&philo->right_fork->fork);
	}
    return (0);
}

int philo_eat_v4(t_philo *philo)
{
    if (philo->action == 'T' && philo->right_fork->state == AVAILABLE
		&& philo->left_fork->state == AVAILABLE
		&& (philo->num_of_times_eaten
			<= philo->right_fork->right_philo->num_of_times_eaten)
		&& (philo->num_of_times_eaten
			<= philo->left_fork->left_philo->num_of_times_eaten))
        return (TRUE);
    return (FALSE);
}

t_philo *philo_eat_v5(t_philo *philo)
{
    size_t  time;

    philo = philo_eat_v1(philo);
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

t_philo *philo_eat_v6(t_philo *philo)
{
    philo->right_fork->state = AVAILABLE;
	philo->left_fork->state = AVAILABLE;
	philo->num_of_times_eaten++;
    return (philo);
}
