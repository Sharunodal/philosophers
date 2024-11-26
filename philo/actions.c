/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:12:17 by arissane          #+#    #+#             */
/*   Updated: 2024/11/07 12:18:49 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_status(t_philo *philo)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->complete == 1)
		check = 1;
	pthread_mutex_unlock(&philo->data->lock);
	return (check);
}

int	wait_given_time(t_philo *philo, size_t wait_time)
{
	if (wait_time > (philo->data->time_to_die * 1000))
		wait_time = (philo->data->time_to_die * 1000);
	if (ft_usleep(philo, wait_time) == -1)
		return (1);
	return (0);
}

int	go_to_bed(t_philo *philo)
{
	if (threadsafe_printf(philo, "is sleeping") == 1)
		return (1);
	if (wait_given_time(philo, philo->data->time_to_sleep) == 1)
		return (1);
	if (threadsafe_printf(philo, "is thinking") == 1)
		return (1);
	return (0);
}

int	eat(t_philo *philo)
{
	size_t	time_taken;
	int		check;

	pthread_mutex_lock(&philo->data->lock);
	update_philo_status(philo, 2);
	time_taken = current_time(philo->data) - philo->data->start_time;
	printf("%zu %d is eating\n", time_taken, philo->id);
	if (philo->times_eaten == philo->data->must_eat
		&& philo->data->must_eat != 0)
	{
		philo->data->number_full++;
	}
	pthread_mutex_unlock(&philo->data->lock);
	check = wait_given_time(philo, philo->data->time_to_eat);
	update_philo_status(philo, 0);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	return (check);
}

int	take_forks(t_philo *philo)
{
	if (check_status(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	if (threadsafe_printf(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		return (1);
	}
	if (philo->data->number_of_philosophers == 1)
	{
		wait_given_time(philo, philo->data->time_to_die * 1000);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	if (threadsafe_printf(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
		return (1);
	}
	return (0);
}
