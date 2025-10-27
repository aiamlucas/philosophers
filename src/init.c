#include "philo.h"

static void	cleanup_partial_init(t_data *data, int stage)
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
	int	i;
	data->chopsticks = NULL;
	data->philos = NULL;
	data->n_philos = logos->n_philos;
	data->time_to_die = logos->time_to_die;
	data->time_to_eat = logos->time_to_eat;
	data->time_to_sleep = logos->time_to_sleep;
	data->must_eat_count = logos->must_eat_count;
	data->start_time = get_time_ms();
	data->dead_flag = 0;
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
