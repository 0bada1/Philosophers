/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:04:06 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/23 14:04:07 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_2d(void **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			if (array[i] != NULL)
				free(array[i++]);
		}
		free(array);
	}
}

void	free_everything(t_node *philos)
{
	if (!philos)
		return ;
	free_2d((void **)philos->philosopher);
	free_2d((void **)philos->forks);
	if (philos)
		free(philos);
	return ;
}

void	destroy_mutexes(t_node *philos)
{
	t_counter	count;

	count.i = 0;
	while (philos->forks[count.i])
		pthread_mutex_destroy(&philos->forks[count.i++]->fork);
	pthread_mutex_destroy(&philos->print_lock);
	free_everything(philos);
	return ;
}
