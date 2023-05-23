/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 07:04:17 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/23 14:10:50 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*philo_life(t_philo *philo)
{
	size_t	time;

	if (!philo)
		return (NULL);
	pthread_mutex_lock(&philo->node->simulation_lock);
	if (philo->node->simulation_status == FALSE)
		return (pthread_mutex_unlock(&philo->node->simulation_lock), philo);
	pthread_mutex_unlock(&philo->node->simulation_lock);
	time = allocate_time(philo);
	pthread_mutex_lock(&philo->life_mutex);
	philo->life -= time - philo->num;
	philo->num = time;
	pthread_mutex_unlock(&philo->life_mutex);
	philo = philo_life_v1(philo, time);
	philo = philo_life_v2(philo);
	return (philo);
}

//  && (philo->num_of_times_eaten <= 
// philo->right_fork->right_philo->num_of_times_eaten) && 
// (philo->num_of_times_eaten <= 
// philo->left_fork->left_philo->num_of_times_eaten)
t_philo	*philo_eat(t_philo *philo)
{
	size_t	time;

	if (!philo)
		return (NULL);
	time = 0;
	pthread_mutex_lock(&philo->node->simulation_lock);
	if (philo->node->simulation_status == FALSE)
		return (pthread_mutex_unlock(&philo->node->simulation_lock), philo);
	pthread_mutex_unlock(&philo->node->simulation_lock);
	lock_forks(philo);
	if (philo_eat_v4(philo) == TRUE && (int)time > -1)
	{
		philo = philo_eat_v5(philo);
		philo = philo_eat_v3(philo);
		time = allocate_time(philo);
		pthread_mutex_lock(&philo->node->simulation_lock);
		if (philo->node->simulation_status == FALSE)
			return (pthread_mutex_unlock(&philo->node->simulation_lock), philo);
		pthread_mutex_unlock(&philo->node->simulation_lock);
		ft_usleep(philo, philo->time_of_eating, philo->node->time_to_eat);
		lock_forks(philo);
		philo = philo_eat_v6(philo);
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (pthread_mutex_unlock(&philo->right_fork->fork), philo);
}

t_philo	*philo_sleep(t_philo *philo)
{
	size_t	time;

	if (!philo)
		return (NULL);
	time = allocate_time(philo);
	if (philo->action == 'E' && (time - philo->time_of_eating)
		>= philo->node->time_to_eat)
	{
		philo->action = 'S';
		philo->time_of_sleeping = time;
		call_life_and_mutex(philo);
		if (philo->node->simulation_status == TRUE)
		{
			pthread_mutex_unlock(&philo->node->simulation_lock);
			pthread_mutex_lock(&philo->node->print_lock);
			if (philo->node->simulation_status == TRUE)
				printf(BLUE"%li Philo %i is sleeping\n"WHITE,
					time, philo->philo_id + 1);
			pthread_mutex_unlock(&philo->node->print_lock);
		}
		else
			pthread_mutex_unlock(&philo->node->simulation_lock);
		ft_usleep(philo, philo->time_of_sleeping, philo->node->time_to_sleep);
	}
	return (philo);
}

t_philo	*philo_think(t_philo *philo)
{
	size_t	time;

	if (!philo)
		return (NULL);
	time = allocate_time(philo);
	if (check_think_condition(philo, time) == TRUE)
	{
		philo = philo_think_v1(philo);
		pthread_mutex_lock(&philo->node->simulation_lock);
		if (philo->node->simulation_status == TRUE)
		{
			pthread_mutex_unlock(&philo->node->simulation_lock);
			if (philo->node->simulation_status == TRUE)
			{
				usleep(100);
				pthread_mutex_lock(&philo->node->print_lock);
				printf(YELLOW"%li Philo %i is thinking\n"WHITE,
					time, philo->philo_id + 1);
				pthread_mutex_unlock(&philo->node->print_lock);
			}
		}
		else
			pthread_mutex_unlock(&philo->node->simulation_lock);
	}
	return (philo);
}

// t_philo		*philo = (t_philo *)arg;
void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (one_philo(philo) == TRUE)
		return (NULL);
	eat_order(philo);
	while (TRUE)
	{
		pthread_mutex_lock(&philo->node->simulation_lock);
		if (philo->node->simulation_status == FALSE)
		{
			pthread_mutex_unlock(&philo->node->simulation_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->node->simulation_lock);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
