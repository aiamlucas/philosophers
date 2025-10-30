#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>

typedef struct s_data
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	int				dead_flag;
	pthread_mutex_t	*chopsticks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			left_chopstick;
	int			right_chopstick;
	long long	last_meal_time;
	int			meals_eaten;
	t_data		*data;
}	t_philo;

typedef struct s_logos
{
	int	n_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_count;
}	t_logos;

bool		ft_isspace(int c);
bool		ft_safe_atoi(const char *str, int *result);
bool		validate_number_format(const char *str);
bool		is_valid_integer(const char *str);
bool		validate_args(int argc, char *argv[]);
bool		parse_logos(t_logos *logos, int argc, char *argv[]);
bool		init_simulation(t_logos *logos);
bool		init_data(t_data *data, t_logos *logos);
bool		init_chopsticks(t_data *data);
bool		init_mutexes(t_data *data);
bool		init_philosophers(t_data *data);
long long	get_time_ms(void);
void		ft_usleep_check(t_data *data, long long milliseconds);
void		*philosopher_routine(void *arg);
void		print_status(t_philo *philo, char *status);
void		take_chopsticks(t_philo *philo);
void		drop_chopsticks(t_philo *philo);
void		monitor_simulation(t_data *data);
bool		simulation_ended(t_data *data);
bool		all_philos_ate_enough(t_data *data);
bool		validate_philo_count(int n_philos);
bool		validate_timings(t_logos *logos);
bool		validate_must_eat(int must_eat_count);
void		cleanup_partial_init(t_data *data, int stage);
void		cleanup(t_data *data);

#endif
