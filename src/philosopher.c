/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:34:20 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/22 13:29:46 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	handle_single_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%d 1 died\n", data->time_to_die);
}

static bool	philo_eat(t_philo *philo)
{
	take_forks(philo);
	if (simulation_ended(philo->data))
	{
		drop_forks(philo);
		return (false);
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_usleep_check(philo->data, philo->data->time_to_eat);
	drop_forks(philo);
	return (true);
}

static bool	philo_sleep(t_philo *philo)
{
	if (simulation_ended(philo->data))
		return (false);
	print_status(philo, "is sleeping");
	ft_usleep_check(philo->data, philo->data->time_to_sleep);
	return (true);
}

static bool	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	if (simulation_ended(philo->data))
		return (false);
	return (true);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!simulation_ended(philo->data))
	{
		if (!philo_think(philo))
			break ;
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
	}
	return (NULL);
}
