/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:33:28 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/22 13:35:26 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

bool	create_threads(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(
				&data->philos[i].thread,
				NULL, philosopher_routine,
				&data->philos[i]) != 0)
		{
			printf("Error: failed to create philosopher thread %d\n", i + 1);
			data->dead_flag = 1;
			j = 0;
			while (j < i)
			{
				pthread_join(data->philos[j].thread, NULL);
				j++;
			}
			return (false);
		}
		i++;
	}
	return (true);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
