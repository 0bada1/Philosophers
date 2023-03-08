/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 03:17:23 by ooutabac          #+#    #+#             */
/*   Updated: 2023/01/27 03:27:35 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_input(char *argv[])
{
	t_counter	count;

	count.i = 1;
	while (argv[count.i])
	{
		count.j = 0;
		while (argv[count.i][count.j])
		{
			if (ft_isdigit(argv[count.i][count.j]) == 0)
				return (-1);
			count.j++;
		}
		count.i++;
	}
	return (0);
}