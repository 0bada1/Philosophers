/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 06:00:14 by ooutabac          #+#    #+#             */
/*   Updated: 2023/01/27 03:32:38 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "libft/libft.h"

#define TRUE 0
#define FALSE 1

typedef struct s_counter
{
	int	i;
	int	j;
	int	k;
	int	x;
	int	y;
	int	trigger;
}
t_counter;

typedef struct s_philosopher
{
	pthread_t				*thread;
	int						state;
	int						life;
	struct s_philosopher	*right_fork;
	struct s_philosopher	*left_fork;
}
t_philosopher;

typedef struct s_node
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_to_eat;
	t_philosopher	*philosopher;
}t_node;

/*-------------------------------PHILOSOPHERS-------------------------------*/
/*---------------------------------PARSING----------------------------------*/
t_node		*parsing(int argc, char *argv[]);

/*-------------------------------CHECK_ERRORS-------------------------------*/
int			check_input(char *argv[]);

/*-----------------------------------FREE-----------------------------------*/