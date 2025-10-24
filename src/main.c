#include "philo.h"

static int	init_logos(t_logos *logos, char *argv[])
{
	if (!logos || !argv)
		return (EXIT_FAILURE);
	if (!ft_safe_atoi(argv[1], &logos->n_philos))
		return (EXIT_FAILURE);
	if (!ft_safe_atoi(argv[2], &logos->time_to_die))
		return (EXIT_FAILURE);
	if (!ft_safe_atoi(argv[3], &logos->time_to_eat))
		return (EXIT_FAILURE);
	if (!ft_safe_atoi(argv[4], &logos->time_to_sleep))
		return (EXIT_FAILURE);
	if (logos->n_philos <= 0 || logos->time_to_die <= 0
		|| logos->time_to_eat <= 0 || logos->time_to_sleep <= 0)
		return (EXIT_FAILURE);
	if (logos->n_philos > 200)
	{
		printf("Error: too many philosopers (max  200)\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	t_logos	logos;
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo <number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [must_eat_count]\n");
		return (EXIT_FAILURE);
	}
	if  (init_logos(&logos, argv) == EXIT_FAILURE)
	{
		printf("Error: invalid arguments\n");
		return (EXIT_FAILURE);

	}

	printf("Configuration loaded successfullly:\n");
	printf(" Philosophers: %d\n", logos.n_philos);
	printf(" Time to die: %d ms\n", logos.time_to_die);
	printf(" Time to eat %d ms\n", logos.time_to_eat);
	printf(" Time to sleep %d ms\n", logos.time_to_sleep);
	return (EXIT_SUCCESS);
}
