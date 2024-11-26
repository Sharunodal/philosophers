/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:36:48 by arissane          #+#    #+#             */
/*   Updated: 2024/11/07 12:18:10 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allocate_threads(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
	{
		free(data->philos);
		return (1);
	}
	return (0);
}

static void	init_philos(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].id = (i + 1);
		data->philos[i].times_eaten = 0;
		data->philos[i].status = 0;
		data->philos[i].previous_meal_time = current_time(data);
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = (i + 1) % data->number_of_philosophers;
		data->philos[i].data = data;
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

static void	init_data(t_data *data, char **argv)
{
	data->number_of_philosophers = ft_atost(argv[1]);
	data->time_to_die = ft_atost(argv[2]);
	data->time_to_eat = ft_atost(argv[3]) * 1000;
	data->time_to_sleep = ft_atost(argv[4]) * 1000;
	data->number_full = 0;
	data->complete = 0;
	pthread_mutex_init(&data->lock, NULL);
	if (argv[5])
		data->must_eat = ft_atost(argv[5]);
	else
		data->must_eat = 0;
}

static int	validate(char **argv)
{
	int	i;
	int	k;

	i = 1;
	while (argv[i])
	{
		k = 0;
		while (argv[i][k])
		{
			if (argv[i][0] == '0')
				return (1);
			if (argv[i][k] < '0' || argv[i][k] > '9')
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

int	initialise(t_data *data, char **argv)
{
	if (validate(argv) == 1)
	{
		printf("invalid arguments\n");
		return (1);
	}
	init_data(data, argv);
	if (allocate_threads(data) == 1)
	{
		printf("allocation error\n");
		return (1);
	}
	init_philos(data);
	data->start_time = current_time(data);
	return (0);
}
