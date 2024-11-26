/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:50:30 by arissane          #+#    #+#             */
/*   Updated: 2024/11/20 10:56:15 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	instructions(void)
{
	printf("Please use the following format:\n");
	printf("\"./philo 1 2 3 4 5\"\n");
	printf("1 = number of philosophers\n");
	printf("2 = time until death\n");
	printf("3 = time it takes to eat\n");
	printf("4 = time it takes to sleep\n");
	printf("5 = number of times one must eat(optional)\n");
	return (1);
}

static void	*survive(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	if (philo->id % 2 == 0)
	{
		threadsafe_printf(philo, "is thinking");
		if (wait_given_time(philo, philo->data->time_to_eat) == 1)
			return (NULL);
	}
	else
		threadsafe_printf(philo, "is thinking");
	while (1)
	{
		if (take_forks(philo) == 1)
			break ;
		if (eat(philo) == 1)
			break ;
		if (go_to_bed(philo) == 1)
			break ;
	}
	return (NULL);
}

static int	create_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philos[i].thread, NULL, survive,
				(void *) &data->philos[i]) != 0)
		{
			terminate_threads(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	print_exit(t_data *data, int code)
{
	size_t	time;

	if (code == -1)
		printf("%zu philosophers had enough to eat\n", data->number_full);
	else
	{
		time = current_time(data) - data->start_time;
		printf("%zu %d died\n", time, code);
	}
}

int	main(int argc, char **argv)
{
	size_t		i;
	t_data		data;
	int			exit_code;

	if (argc < 5 || argc > 6)
		return (instructions());
	if (initialise(&data, argv) == 1)
		return (1);
	if (create_threads(&data) == 1)
		return (1);
	exit_code = observer(&data);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	if (exit_code != 0)
		print_exit(&data, exit_code);
	free_data(&data);
	return (0);
}
