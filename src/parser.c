#include "philo.h"

bool	validate_number_format(const char *str)
{
	if (!*str)
		return (false);
	if (*str < '0' || *str > '9')
		return (false);
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str && ft_isspace(*str))
		str++;
	if (*str != '\0')
		return (false);
	return (true);
}

bool	is_valid_integer(const char *str)
{
	const char	*num_start;
	int			dummy_value;

	if (!str || !*str)
		return (false);
	while (*str && ft_isspace(*str))
		str++;
	if (!*str)
		return (false);
	num_start = str;
	if (*str == '-')
		return (false);
	if (*str == '+')
		str++;
	if (!*str || !(*str >= '0' && *str <= '9'))
		return (false);
	if (!validate_number_format(str))
		return (false);
	return (ft_safe_atoi(num_start, &dummy_value));
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
			printf("Error: Invalid argument '%s' (must be a positive number)\n", argv[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	validate_ranges(t_logos *logos)
{
	if (logos->n_philos <= 0)
	{
		printf("Error: Number of philosophers must be positive\n");
		return (false);
	}
	if (logos->n_philos > 200)
	{
		printf("Error: Too many philosophers (max 200)\n");
		return (false);
	}
	if (logos->time_to_die <= 0)
	{
		printf("Error: time_to_die must be positive\n");
		return (false);
	}
	if (logos->time_to_eat <= 0)
	{
		printf("Error: time_to_eat must be positive\n");
		return (false);
	}
	if (logos->time_to_sleep <= 0)
	{
		printf("Error: time_to_sleep must be positive\n");
		return (false);
	}
	if (logos->must_eat_count != -1 && logos->must_eat_count <= 0)
	{
		printf("Error: must_eat_count must be positive\n");
		return (false);
	}
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
