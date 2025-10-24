#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>

typedef struct	s_logos
{
	int	n_philos; 
    int	time_to_die;
    int	time_to_eat; 
    int	time_to_sleep;
}	t_logos;


int	ft_safe_atoi(const char *str, int *result);

#endif
