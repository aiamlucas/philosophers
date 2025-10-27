#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long milliseconds)
{
	long long start;

	start = get_time_ms();
	while (get_time_ms() - start < milliseconds)
		usleep(500);
}

void	print_status(t_philo *philo, char *status)
{
	long long timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->dead_flag)
	{
		timestamp = get_time_ms() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	take_chopsticks(t_philo *philo)
{
	int	first;
	int	second;

	if (philo->left_chopstick < philo->right_chopstick)
	{
		first = philo->left_chopstick;
		second = philo->right_chopstick;
	}
	else
	{
		first = philo->right_chopstick;
		second = philo->left_chopstick;
	}
	pthread_mutex_lock(&philo->data->chopsticks[first]);
	print_status(philo, "has taken a chopstick");
	pthread_mutex_lock(&philo->data->chopsticks[second]);
	print_status(philo, "has taken a chopstick");
}

void	drop_chopsticks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->chopsticks[philo->left_chopstick]);
	pthread_mutex_unlock(&philo->data->chopsticks[philo->right_chopstick]);
}
