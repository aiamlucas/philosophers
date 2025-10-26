#include "philo.h"

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
