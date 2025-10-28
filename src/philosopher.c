#include "philo.h"

static bool	philo_eat(t_philo *philo)
{
	take_chopsticks(philo);
	if (simulation_ended(philo->data))
	{
		drop_chopsticks(philo);
		return (false);
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_usleep_check(philo->data, philo->data->time_to_eat);
	drop_chopsticks(philo);
	return (true);
}

static bool	philo_sleep(t_philo *philo)
{
	if (simulation_ended(philo->data))
		return (false);
	print_status(philo, "is sleeping");
	ft_usleep_check(philo->data, philo->data->time_to_sleep);
	return (true);
}

static bool philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	if (simulation_ended(philo->data))
		return (false);
	return (true);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!simulation_ended(philo->data))
	{
		if (!philo_think(philo))
			break ;
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
	}
	return (NULL);
}
