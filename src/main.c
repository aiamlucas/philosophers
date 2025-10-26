#include "philo.h"

int main(int argc, char *argv[])
{
	t_logos	logos;

	if (!validate_args(argc, argv))
		return (EXIT_FAILURE);
	if (!parse_logos(&logos, argc, argv))
	{
		printf("Error: Failed to parse arguments\n");
		return (EXIT_FAILURE);
	}
	if (!init_simulation(&logos))
	{
		printf("Error: Failed to initialize simulation\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
