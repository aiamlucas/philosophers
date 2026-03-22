/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:33:25 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/22 13:31:58 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

void	cleanup_partial_init(t_data *data, int stage)
{
	int	i;

	if (stage >= 4 && data->philos)
		free(data->philos);
	if (stage >= 3)
		pthread_mutex_destroy(&data->death_mutex);
	if (stage >= 2)
		pthread_mutex_destroy(&data->print_mutex);
	if (stage >= 1 && data->forks)
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
}

bool	init_data(t_data *data, t_logos *logos)
{
	data->forks = NULL;
	data->philos = NULL;
	data->n_philos = logos->n_philos;
	data->time_to_die = logos->time_to_die;
	data->time_to_eat = logos->time_to_eat;
	data->time_to_sleep = logos->time_to_sleep;
	data->must_eat_count = logos->must_eat_count;
	data->start_time = get_time_ms();
	data->dead_flag = 0;
	if (!init_forks(data))
		return (false);
	if (!init_mutexes(data))
		return (false);
	if (!init_philosophers(data))
		return (false);
	return (true);
}

bool	init_program(t_logos *logos, t_data *data, int argc, char *argv[])
{
	if (!validate_args(argc, argv))
		return (false);
	if (!parse_logos(logos, argc, argv))
		return (false);
	if (!init_data(data, logos))
	{
		printf("Error: failed to initialize data\n");
		return (false);
	}
	return (true);
}
