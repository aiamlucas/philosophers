#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!simulation_ended(philo->data))
	{
		print_status(philo, "is thinking");
		if (simulation_ended(philo->data))
			break ;
		take_chopsticks(philo);
		if (simulation_ended(philo->data))
		{
			drop_chopsticks(philo);
			break ;
		}
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->last_meal_time = get_time_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->death_mutex);
		ft_usleep_check(philo->data, philo->data->time_to_eat);
		drop_chopsticks(philo);
		if (simulation_ended(philo->data))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep_check(philo->data, philo->data->time_to_sleep);
	}
	return (NULL);
}
