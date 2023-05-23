/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 03:17:23 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/11 20:18:04 by amalbrei         ###   ########.fr       */
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
