/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:39:28 by arissane          #+#    #+#             */
/*   Updated: 2024/11/07 12:20:12 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_pulse(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->lock);
	time = current_time(philo->data) - philo->previous_meal_time;
	pthread_mutex_unlock(&philo->lock);
	if (time > philo->data->time_to_die)
	{
		philo->data->complete = 1;
		return (philo->id);
	}
	return (0);
}

static int	check_full(t_data *data)
{
	if (data->number_full >= data->number_of_philosophers)
	{
		data->complete = 1;
	}
	return (data->complete);
}

static int	check_everyone(t_data *data)
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->lock);
		if (check_full(data) == 1)
			check = -1;
		else
			check = check_pulse(&data->philos[i]);
		i++;
		pthread_mutex_unlock(&data->lock);
		if (check != 0)
			return (check);
	}
	return (0);
}

int	observer(t_data *data)
{
	int	check;

	check = 0;
	while (1)
	{
		usleep(200);
		check = check_everyone(data);
		if (check != 0)
			return (check);
	}
}
