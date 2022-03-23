#ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philothread{
	pthread_t		*th;
	int				id;
}	t_pthred;

typedef struct s_philosophers{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	t_pthred		**info;
}	t_philo;

int	checker_digit(char **argv);

int	checker(int argc, char **argv);

int	ft_atoi(const char *nptr);

int	parce(char **argv, t_philo *st);

#endif