/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:33:56 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/22 13:10:09 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

bool	simulation_ended(t_data *data)
{
	bool	ended;

	pthread_mutex_lock(&data->death_mutex);
	ended = data->dead_flag;
	pthread_mutex_unlock(&data->death_mutex);
	return (ended);
}

bool	all_philos_ate_enough(t_data *data)
{
	int		i;
	bool	result;

	pthread_mutex_lock(&data->death_mutex);
	i = 0;
	result = true;
	while (i < data->n_philos)
	{
		if (data->philos[i].meals_eaten < data->must_eat_count)
		{
			result = false;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}

static bool	check_phil_death(t_data *data, int i)
{
	long long	time_since_meal;

	pthread_mutex_lock(&data->death_mutex);
	time_since_meal = get_time_ms() - data->philos[i].last_meal_time;
	if (time_since_meal > data->time_to_die)
	{
		data->dead_flag = 1;
		pthread_mutex_lock(&data->print_mutex);
		printf(
			"%lld %d died\n",
			get_time_ms() - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (false);
}

void	monitor_simulation(t_data *data)
{
	int			i;

	while (42)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (check_phil_death(data, i))
				return ;
			i++;
		}
		if (data->must_eat_count != -1 && all_philos_ate_enough(data))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return ;
		}
		usleep(1000);
	}
}
