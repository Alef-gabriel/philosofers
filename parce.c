#include "philo.h"

int	parce(char **argv, t_philo *st)
{
	st->number_of_philosophers = ft_atoi(argv[1]);
	st->time_to_die = ft_atoi(argv[2]);
	st->time_to_eat = ft_atoi(argv[3]);
	st->time_to_sleep = ft_atoi(argv[4]);
	st->must_eat = ft_atoi(argv[5]);
	st->start = (struct timeval *)malloc(sizeof(struct timeval));
	return (0);
}