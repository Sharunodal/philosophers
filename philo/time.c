/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:16:37 by arissane          #+#    #+#             */
/*   Updated: 2024/11/08 11:33:48 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	current_time(t_data *data)
{
	struct timeval	time;
	size_t			now;

	if (gettimeofday(&time, NULL) == -1)
	{
		pthread_mutex_lock(&data->lock);
		data->complete = 1;
		printf("timeval error\n");
		pthread_mutex_unlock(&data->lock);
		return (0);
	}
	now = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now);
}

int	ft_usleep(t_philo *philo, size_t limit)
{
	size_t	time;
	size_t	start;
	int		counter;

	time = 0;
	counter = 0;
	limit = limit / 1000;
	start = current_time(philo->data);
	while (time < limit)
	{
		usleep(100);
		counter++;
		if (counter % 10 == 0)
		{
			if (check_status(philo) == 1)
				return (1);
		}
		time = current_time(philo->data) - start;
	}
	return (0);
}
