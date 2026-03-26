/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:33:35 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/22 19:40:53 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->n_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
}

void	cleanup(t_data *data)
{
	destroy_mutexes(data);
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

void	cleanup_partial_init(t_data *data, t_init_stage stage)
{
	int	i;

	if (stage >= STAGE_INIT_PHILOS && data->philos)
		free(data->philos);
	if (stage >= STAGE_INIT_DEATH_MUTEX)
		pthread_mutex_destroy(&data->death_mutex);
	if (stage >= STAGE_INIT_PRINT_MUTEX)
		pthread_mutex_destroy(&data->print_mutex);
	if (stage >= STAGE_INIT_FORKS && data->forks)
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
