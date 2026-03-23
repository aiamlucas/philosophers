/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:33:25 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/23 16:03:44 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

bool	init_data(t_data *data, t_logos *logos)
{
	data->forks = NULL;
	data->philos = NULL;
	data->n_philos = logos->n_philos;
	data->time_to_die = (long long)logos->time_to_die;
	data->time_to_eat = (long long)logos->time_to_eat;
	data->time_to_sleep = (long long)logos->time_to_sleep;
	data->must_eat_count = logos->must_eat_count;
	data->start_time = get_time_ms();
	data->dead_flag = 0;
	if (!init_forks_mutexes(data))
		return (false);
	if (!init_print_death_mutexes(data))
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
