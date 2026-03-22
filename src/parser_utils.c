/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:34:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/22 12:34:12 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

bool	validate_philo_count(int n_philos)
{
	if (n_philos <= 0)
	{
		printf("Error: Number of philosophers must be positive\n");
		return (false);
	}
	if (n_philos > 200)
	{
		printf("Error: Too many philosophers (max 200)\n");
		return (false);
	}
	return (true);
}

bool	validate_timings(t_logos *logos)
{
	if (logos->time_to_die <= 0)
	{
		printf("Error: time_to_die must be positive\n");
		return (false);
	}
	if (logos->time_to_eat <= 0)
	{
		printf("Error: time_to_eat must be positive\n");
		return (false);
	}
	if (logos->time_to_sleep <= 0)
	{
		printf("Error: time_to_sleep must be positive\n");
		return (false);
	}
	return (true);
}

bool	validate_must_eat(int must_eat_count)
{
	if (must_eat_count != -1 && must_eat_count <= 0)
	{
		printf("Error: must_eat_count must be positive\n");
		return (false);
	}
	return (true);
}
