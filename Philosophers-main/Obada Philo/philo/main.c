/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:03:54 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/23 14:03:54 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_node	*check_life_loop(t_node *philos)
{
	t_counter	count;

	count.i = 0;
	while (1)
	{
		philo_life(philos->philosopher[count.i++]);
		if (count.i == philos->num_of_philos - 1)
			count.i = 0;
		pthread_mutex_lock(&philos->simulation_lock);
		if (philos->simulation_status == FALSE)
		{
			pthread_mutex_unlock(&philos->simulation_lock);
			break ;
		}
		pthread_mutex_unlock(&philos->simulation_lock);
	}
	return (philos);
}

int	create_simulation(t_node *philos)
{
	t_counter	count;

	count.i = 0;
	while (philos->philosopher[count.i])
	{
		if (pthread_create(&philos->philosopher[count.i]->thread, NULL,
				philo_thread, philos->philosopher[count.i]) != 0)
			return (printf("Error from pthread_create\n"), -1);
		count.i++;
	}
	philos = check_life_loop(philos);
	count.i = 0;
	while (philos->philosopher[count.i])
	{
		if (pthread_join(philos->philosopher[count.i]->thread, NULL) != 0)
			return (printf("Error from pthread_join\n"), -2);
		count.i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_node			*philos;

	philos = parsing(argc, argv);
	if (!philos)
		return (printf("Invalid input\n"), 0);
	gettimeofday(&philos->tv, NULL);
	philos->starting_time = (philos->tv.tv_sec * 1000LL)
		+ (philos->tv.tv_usec / 1000LL);
	create_simulation(philos);
	destroy_mutexes(philos);
	return (0);
}
		// printf("numnber of philosophers = %i\n", philos->num_of_philos);
		// printf("time to die = %i\n", philos->time_to_die);
		// printf("time to eat = %i\n", philos->time_to_eat);
		// printf("time to sleep = %i\n", philos->time_to_sleep);
		// if (argc == 6)
			// printf("number of times to eat = %i\n", 
			// philos->number_of_times_to_eat);
		// if (pthread_create(&t1, NULL, &time_thread, philos) != 0)
		// 	return (printf("Error from pthread_create\n"), -1);
		// for (int i = 0; philos->philosopher[i] != NULL; i++)
		// 	printf("Philo[%i] owns forks %i & %i\n",
			// philos->philosopher[i]->philo_id,
			// philos->philosopher[i]->right_fork->fork_id,
			// philos->philosopher[i]->left_fork->fork_id);