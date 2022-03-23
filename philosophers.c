#include "philo.h"

pthread_mutex_t	mut;

void	*hander(void *args)
{
	t_pthred	*info;

	info = (t_pthred *)args;
	pthread_mutex_lock(&mut);
	printf("hey thread %d\n", info->id);
	usleep(100000);
	pthread_mutex_unlock(&mut);
}

t_pthred	**info_inicialize(int size)
{
	pthread_t	*th;
	t_pthred	**info;
	int			i;

	i = 0;
	info = (t_pthred **)malloc(sizeof(t_pthred *) * size);
	while (i < size)
	{
		info[i] = (t_pthred *)malloc(sizeof(t_pthred));
		info[i]->id = i;
		info[i]->th = (pthread_t *)malloc(sizeof(pthread_t));
		i++;
	}
	return (info);
}

int	main(int argc, char *argv[])
{
	t_philo		philo;
	int i = 0;

	if (checker(argc, argv) == 1)
		return (1);
	parce(argv, &philo);
	philo.info = info_inicialize(philo.number_of_philosophers);
	pthread_mutex_init(&mut, NULL);
	while (philo.number_of_times_each_philosopher_must_eat)
	{
		i = 0;
		while (i < philo.number_of_philosophers)
		{
			pthread_create(philo.info[i]->th, NULL, &hander, philo.info[i]);
			i++;
		}
		philo.number_of_times_each_philosopher_must_eat--;
	}
	i = 0;
	while (i < philo.number_of_philosophers)
	{
		pthread_join(*(philo.info[i]->th), NULL);
		i++;
	}
	pthread_mutex_destroy(&mut);
	return (0);
}