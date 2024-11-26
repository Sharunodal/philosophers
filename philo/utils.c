/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:17:12 by arissane          #+#    #+#             */
/*   Updated: 2024/11/20 12:01:27 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atost(const char *str)
{
	size_t	i;
	size_t	check;
	size_t	number;

	i = 0;
	number = 0;
	while (str[i])
	{
		if (str[i] <= '0' && str[i] >= '9')
			return (0);
		check = number;
		number = number * 10;
		if ((number / 10) != check)
			return (0);
		number = number + (str[i] - 48);
		i++;
	}
	return (number);
}

int	threadsafe_printf(t_philo *philo, char *str)
{
	size_t	time_taken;

	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->complete == 1)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	time_taken = current_time(philo->data) - philo->data->start_time;
	printf("%zu %d %s\n", time_taken, philo->id, str);
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->philos[i].lock);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	free(data->forks);
	free(data->philos);
}

void	terminate_threads(t_data *data, size_t i)
{
	size_t	k;

	k = 0;
	pthread_mutex_lock(&data->lock);
	data->complete = 1;
	printf("the creation of a thread failed\n");
	pthread_mutex_unlock(&data->lock);
	while (k < i)
	{
		pthread_join(data->philos[k].thread, NULL);
		k++;
	}
	free_data(data);
}

void	update_philo_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->lock);
	philo->status = status;
	if (status == 2)
	{
		philo->times_eaten++;
		philo->previous_meal_time = current_time(philo->data);
	}
	pthread_mutex_unlock(&philo->lock);
}
