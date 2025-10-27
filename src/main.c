#include "philo.h"
#include <stdlib.h>

static void	handle_single_philo(t_data *data)
{
	printf(" 0 1 has taken a chopstick\n");
	usleep(data->time_to_die * 1000);
	printf("%d 1 died\n", data->time_to_die);
}

int main(int argc, char *argv[])
{
	t_logos	logos;
	t_data	data;
	int		i;

	if (!validate_args(argc, argv))
		return (EXIT_FAILURE);
	if (!parse_logos(&logos, argc, argv))
		return (EXIT_FAILURE);
	if (!init_simulation(&logos))
		return (EXIT_FAILURE);
	if (!init_data(&data, &logos))
		return (EXIT_FAILURE);
	if (data.n_philos == 1)
	{
		handle_single_philo(&data);
		cleanup(&data);
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (i < data.n_philos)
	{
		pthread_create(&data.philos[i].thread, NULL, philosopher_routine, &data.philos[i]);
		i++;
	}
	monitor_simulation(&data);
	usleep(10000);
	i = 0;
	while (i < data.n_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	cleanup(&data);
	return (EXIT_SUCCESS);
}
