/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:34:04 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/23 11:40:02 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <limits.h>

bool	is_valid_integer(const char *str)
{
	int			dummy_value;

	if (!str || !*str)
		return (false);
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		return (false);
	return (ft_safe_atoi(str, &dummy_value));
}

bool	validate_args(int argc, char *argv[])
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		printf("Usage: ./philo <number_of_philos> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> [must_eat_count]\n");
		return (false);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_integer(argv[i]))
		{
			printf(
				"Error: Invalid argument '%s' (must be a positive number between 1 and %d)\n",
				argv[i], INT_MAX);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	validate_ranges(t_logos *logos)
{
	if (!validate_philo_count(logos->n_philos))
		return (false);
	if (!validate_timings(logos))
		return (false);
	if (!validate_must_eat(logos->must_eat_count))
		return (false);
	return (true);
}

bool	parse_logos(t_logos *logos, int argc, char *argv[])
{
	if (!logos || !argv)
		return (false);
	if (!ft_safe_atoi(argv[1], &logos->n_philos))
		return (false);
	if (!ft_safe_atoi(argv[2], &logos->time_to_die))
		return (false);
	if (!ft_safe_atoi(argv[3], &logos->time_to_eat))
		return (false);
	if (!ft_safe_atoi(argv[4], &logos->time_to_sleep))
		return (false);
	if (argc == 6)
	{
		if (!ft_safe_atoi(argv[5], &logos->must_eat_count))
			return (false);
	}
	else
		logos->must_eat_count = -1;
	if (!validate_ranges(logos))
		return (false);
	return (true);
}
