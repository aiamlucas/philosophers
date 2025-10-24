#include "philo.h"

static bool	is_overflow(int num, int digit, int signal)
{
	if (signal == 1)
	{
		if (num > (INT_MAX - digit) / 10)
			return (true);
	}
	else
	{
		if (num > ((-(long long)INT_MIN) - digit) / 10)
			return (true);
	}
	return (false);
}

static const char	*skip_whitespace(const char *str)
{
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	return (str);
}

static const char	*parse_signal(const char *str, int *signal)
{
	*signal = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*signal = -1;
		str++;
	}
	return (str);
}

bool	ft_safe_atoi(const char *str, int *result)
{
	int	signal;
	int	num;
	int	digit;

	num = 0;
	str = skip_whitespace(str);
	str = parse_signal(str, &signal);
	if (!(*str >= '0' && *str <= '9'))
		return (false);
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (is_overflow(num, digit, signal))
			return (false);
		num = num * 10 + digit;
		str++;
	}
	str = skip_whitespace(str);
	if (*str != '\0')
		return (false);
	*result = num * signal;
	return (true);
}
