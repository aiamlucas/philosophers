/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:33:50 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/03/22 13:37:07 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_logos	logos;
	t_data	data;

	if (!init_program(&logos, &data, argc, argv))
		return (EXIT_FAILURE);
	if (data.n_philos == 1)
	{
		handle_single_philo(&data);
		cleanup(&data);
		return (EXIT_SUCCESS);
	}
	if (!create_threads(&data))
	{
		cleanup(&data);
		return (EXIT_FAILURE);
	}
	monitor_simulation(&data);
	usleep(10000);
	join_threads(&data);
	cleanup(&data); 
	return (EXIT_SUCCESS); 
}
