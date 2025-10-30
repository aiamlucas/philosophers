#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	cleanup_partial_init(t_data *data, int stage)
{
	int	i;

	if (stage >= 4 && data->philos)
		free(data->philos);
	if (stage >= 3)
		pthread_mutex_destroy(&data->death_mutex);
	if (stage >= 2)
		pthread_mutex_destroy(&data->print_mutex);
	if (stage >= 1 && data->chopsticks)
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_destroy(&data->chopsticks[i]);
			i++;
		}
		free(data->chopsticks);
	}
}

bool	init_simulation(t_logos *logos)
{
	printf("Dinner table ready\n");
	printf(" Philosophers: %d\n", logos->n_philos);
	printf(" Time to die: %d ms\n", logos->time_to_die);
	printf(" Time to eat: %d ms\n", logos->time_to_eat);
	printf(" Time to sleep: %d ms\n", logos->time_to_sleep);
	if (logos->must_eat_count != -1)
		printf(" Must eat count: %d times\n", logos->must_eat_count);
	else
		printf(" Must eat count: unlimited\n");
	return (true);
}

bool	init_data(t_data *data, t_logos *logos)
{
	data->chopsticks = NULL;
	data->philos = NULL;
	data->n_philos = logos->n_philos;
	data->time_to_die = logos->time_to_die;
	data->time_to_eat = logos->time_to_eat;
	data->time_to_sleep = logos->time_to_sleep;
	data->must_eat_count = logos->must_eat_count;
	data->start_time = get_time_ms();
	data->dead_flag = 0;
	if (!init_chopsticks(data))
		return (false);
	if (!init_mutexes(data))
		return (false);
	if (!init_philosophers(data))
		return (false);
	return (true);
}
