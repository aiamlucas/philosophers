#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct	s_logos
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
int			validate_args(int argc, char *argv[]);
bool		parse_logos(t_logos *logos, int argc, char *argv[]);
bool		init_simulation(t_logos *logos);
long long	get_time_ms(void);
void		ft_usleep(long long milliseconds);

#endif
