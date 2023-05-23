/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 07:04:17 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/11 21:01:46 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_node	*parsing_v1(t_node *philos)
{
	t_counter	count;

	count.i = 0;
	while (count.i < philos->num_of_philos)
	{
		philos->philosopher[count.i] = malloc(sizeof(t_philo) * 1);
		philos->forks[count.i] = malloc(sizeof(t_fork) * 1);
		philos->forks[count.i]->fork_id = count.i;
		philos->forks[count.i]->state = AVAILABLE;
		pthread_mutex_init(&philos->forks[count.i]->fork, NULL);
		pthread_mutex_init(&philos->philosopher[count.i]->life_mutex, NULL);
		philos->philosopher[count.i]->time_of_eating = 0;
		philos->philosopher[count.i]->num = 0;
		philos->philosopher[count.i]->node = philos;
		philos->philosopher[count.i]->action = 'T';
		philos->philosopher[count.i]->life = philos->time_to_die;
		philos->philosopher[count.i]->philo_id = count.i;
		philos->philosopher[count.i]->num_of_times_eaten = 0;
		count.i++;
	}
	philos->philosopher[count.i] = NULL;
	philos->forks[count.i] = NULL;
	return (philos);
}

t_node	*assign_forks_to_philos(t_node *philos)
{
	t_counter	count;

	count.i = 0;
	while (philos->philosopher[count.i])
	{
		if (count.i == philos->num_of_philos - 1)
		{
			philos->philosopher[count.i]->left_fork = philos->forks[count.i];
			philos->philosopher[count.i]->right_fork = philos->forks[0];
		}
		else
		{
			philos->philosopher[count.i]->left_fork = philos->forks[count.i];
			philos->philosopher[count.i]->right_fork = philos->forks
			[count.i + 1];
		}
		count.i++;
	}
	return (philos);
}

t_node	*assign_philos_to_forks(t_node *philos)
{
	t_counter	count;

	count.i = 0;
	while (philos->forks[count.i])
	{
		if (count.i == 0)
		{
			philos->forks[count.i]->right_philo = philos->philosopher[0];
			philos->forks[count.i]->left_philo = philos->philosopher
			[philos->num_of_philos - 1];
		}
		else
		{
			philos->forks[count.i]->right_philo = philos->philosopher[count.i];
			philos->forks[count.i]->left_philo = philos->philosopher
			[count.i - 1];
		}
		count.i++;
	}
	return (philos);
}

t_node	*parsing(int argc, char *argv[])
{
	t_node		*philos;

	if (check_input(argc, argv) < 0)
		return (NULL);
	philos = ft_calloc(sizeof(t_node), 1);
	philos->num_of_philos = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	philos->simulation_status = TRUE;
	philos->philos_done_eating = 0;
	pthread_mutex_init(&philos->print_lock, NULL);
	pthread_mutex_init(&philos->simulation_lock, NULL);
	if (argc == 6)
		philos->number_of_times_to_eat = ft_atoi(argv[5]);
	else
		philos->number_of_times_to_eat = -2;
	philos->philosopher = ft_calloc(sizeof(t_philo *),
			philos->num_of_philos + 1);
	philos->forks = ft_calloc(sizeof(t_fork *), philos->num_of_philos + 1);
	philos = parsing_v1(philos);
	philos = assign_forks_to_philos(philos);
	philos = assign_philos_to_forks(philos);
	return (philos);
}
