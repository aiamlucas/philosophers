#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

static void	handle_single_philo(t_data *data)
{
	printf("0 1 has taken a chopstick\n");
	usleep(data->time_to_die * 1000);
	printf("%d 1 died\n", data->time_to_die);
}

static bool	init_program(t_logos *logos, t_data *data, int argc, char *argv[])
{
	if (!validate_args(argc, argv))
		return (false);
	if (!parse_logos(logos, argc, argv))
		return (false);
	if (!init_simulation(logos))
		return (false);
	if (!init_data(data, logos))
	{
		printf("Error: failed to initialize data\n");
		return (false);
	}
	return (true);
}

static bool	create_threads(t_data *data)
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

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

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
