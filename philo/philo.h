/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:18:44 by arissane          #+#    #+#             */
/*   Updated: 2024/11/20 10:55:58 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	size_t			times_eaten;
	int				status;
	int				l_fork;
	int				r_fork;
	size_t			previous_meal_time;
	t_data			*data;
	pthread_mutex_t	lock;
}	t_philo;

typedef struct s_data
{
	size_t			number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			must_eat;
	size_t			start_time;
	size_t			number_full;
	int				complete;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
}	t_data;

int		initialise(t_data *data, char **argv);
int		ft_atost(const char *str);
int		take_forks(t_philo *philo);
int		go_to_bed(t_philo *philo);
int		check_status(t_philo *philo);
int		threadsafe_printf(t_philo *philo, char *str);
int		eat(t_philo *philo);
int		wait_given_time(t_philo *philo, size_t wait_time);
size_t	current_time(t_data *data);
void	update_philo_status(t_philo *philo, int status);
int		ft_usleep(t_philo *philo, size_t limit);
int		observer(t_data *data);
void	terminate_threads(t_data *data, size_t i);
void	free_data(t_data *data);

#endif
