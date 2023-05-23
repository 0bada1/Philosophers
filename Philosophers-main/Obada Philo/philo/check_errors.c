/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:04:11 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/23 14:10:38 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_input(int argc, char *argv[])
{
	t_counter	count;

	if (argc != 5 && argc != 6)
		return (-1);
	count.i = 1;
	while (argv[count.i])
	{
		if (!argv[count.i][0])
			return (-2);
		count.j = 0;
		while (argv[count.i][count.j])
		{
			if (ft_isdigit(argv[count.i][count.j]) == 0)
				return (-3);
			count.j++;
		}
		count.i++;
	}
	return (0);
}

int	check_think_condition(t_philo *philo, size_t time)
{
	if (philo->action == 'S' && (time - philo->time_of_sleeping)
		>= philo->node->time_to_sleep)
		return (TRUE);
	return (FALSE);
}
