/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 06:00:14 by ooutabac          #+#    #+#             */
/*   Updated: 2023/05/23 14:10:27 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define AVAILABLE 1
# define NOT_AVAILABLE 0
# define WHITE "\033[0;37m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"

typedef struct s_counter
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	x;
	size_t	y;
	size_t	trigger;
}t_counter;

typedef struct t_fork
{
	pthread_mutex_t	fork;
	struct s_philo	*right_philo;
	struct s_philo	*left_philo;
	int				fork_id;
	int				state;
}t_fork;

typedef struct s_philo
{
	pthread_t				thread;
	pthread_mutex_t			life_mutex;
	struct s_node			*node;
	t_fork					*right_fork;
	t_fork					*left_fork;
	char					action;
	int						life;
	int						philo_id;
	int						num;
	int						num_of_times_eaten;
	int						time_of_eating;
	int						time_of_sleeping;
}t_philo;

typedef struct s_node
{
	t_philo			**philosopher;
	t_fork			**forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	simulation_lock;
	pthread_mutex_t	time_lock;
	struct timeval	tv;
	size_t			starting_time;
	size_t			time_ms;
	size_t			num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_times_to_eat;
	size_t			philos_done_eating;
	int				simulation_status;
}t_node;

/*-------------------------------PHILOSOPHERS-------------------------------*/
t_philo		*philo_life(t_philo *philo);
t_philo		*philo_eat(t_philo *philo);
t_philo		*philo_sleep(t_philo *philo);
t_philo		*philo_think(t_philo *philo);
void		*philo_thread(void *arg);

/*---------------------------------PARSING----------------------------------*/
t_node		*parsing(int argc, char *argv[]);

/*-------------------------------CHECK_ERRORS-------------------------------*/
int			check_input(int argc, char *argv[]);
int			check_think_condition(t_philo *philo, size_t time);

/*-----------------------------------FREE-----------------------------------*/
void		free_everything(t_node *philos);
void		free_2d(void **array);
void		destroy_mutexes(t_node *philos);

/*----------------------------------LIBFT----------------------------------*/
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isdigit(int c);
t_philo		*philo_think_v1(t_philo *philo);

/*----------------------------------UTILS----------------------------------*/
int			get_time(t_philo *philo);
int			get_time2(t_philo *philo);
int			ft_usleep(t_philo *philo, size_t time_of_action,
				size_t time_to_usleep);
int			one_philo(t_philo *philo);
void		eat_order(t_philo *philo);
void		call_life_and_mutex(t_philo *philo);

/*----------------------------------UTILS2---------------------------------*/
t_philo		*philo_eat_v1(t_philo *philo);
t_philo		*philo_eat_v2(t_philo *philo);
t_philo		*philo_life_v1(t_philo *philo, size_t time);
t_philo		*philo_life_v2(t_philo *philo);
size_t		allocate_time(t_philo *philo);

/*----------------------------------UTILS3---------------------------------*/
int			lock_forks(t_philo *philo);
int			philo_eat_v4(t_philo *philo);
t_philo		*philo_eat_v3(t_philo *philo);
t_philo		*philo_eat_v5(t_philo *philo);
t_philo		*philo_eat_v6(t_philo *philo);

#endif