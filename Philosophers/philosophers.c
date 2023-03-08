/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 07:04:17 by ooutabac          #+#    #+#             */
/*   Updated: 2023/01/27 03:35:51 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_node			*philos;
	t_philosopher	philo;
	t_counter		counter;

	if (argc == 5 || argc == 6)
	{
		philos = parsing(argc, argv);
		if (!philos)
			return (printf("Invalid input\n"), 0);
		printf("numnber of philosophers = %i\n", philos->number_of_philosophers);
		printf("time to die = %i\n", philos->time_to_die);
		printf("time to eat = %i\n", philos->time_to_eat);
		printf("time to sleep = %i\n", philos->time_to_sleep);
		if (argc == 6)
			printf("number of times to eat = %i\n", philos->number_of_times_to_eat);
	}
	counter.i = 0;
}

t_node	*parsing(int argc, char *argv[])
{
	t_node		*philos;
	t_counter	count;
	
	count.i = 0;
	if (check_input(argv) < 0 || ft_atoi(argv[1]) > 200)
		return (NULL);
	philos = ft_calloc(sizeof(t_node), 1);
	philos->number_of_philosophers = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philos->number_of_times_to_eat = ft_atoi(argv[5]);
	philos->philosopher = ft_calloc(sizeof(t_philosopher), philos->number_of_philosophers);
	while (count.i != philos->number_of_philosophers)
	{
		philos->philosopher[count.i].right_fork = malloc
	}
	return (philos);
}