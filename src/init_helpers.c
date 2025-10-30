#include "philo.h"
#include <stdlib.h>

bool	init_chopsticks(t_data *data)
{
	int	i;

	data->chopsticks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->chopsticks)
		return (false);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->chopsticks[i], NULL) != 0)
		{
			data->n_philos = i;
			cleanup_partial_init(data, 1);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		cleanup_partial_init(data, 1);
		return (false);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		cleanup_partial_init(data, 2);
		return (false);
	}
	return (true);
}

bool	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
	{
		cleanup_partial_init(data, 3);
		return (false);
	}
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_chopstick = i;
		data->philos[i].right_chopstick = (i + 1) % data->n_philos;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return (true);
}
