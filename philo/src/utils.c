/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:34:26 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/22 12:34:29 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep_check(t_data *data, long long milliseconds)
{
	long long	start;

	start = get_time_ms();
	while (get_time_ms() - start < milliseconds)
	{
		if (simulation_ended(data))
			return ;
		usleep(500);
	}
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;
	bool		is_dead;

	pthread_mutex_lock(&philo->data->death_mutex);
	is_dead = philo->data->dead_flag;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (!is_dead)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		timestamp = get_time_ms() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, status);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}

void	take_forks(t_philo *philo)
{
	int	first;
	int	second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second]);
	print_status(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}
