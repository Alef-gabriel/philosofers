#include "philo.h"

int			eat;
int			eating;
struct timeval	start;

void	*hander(t_pthred *args)
{

	pthread_mutex_lock(args->left_fork->mut);
	printf("[%0.4f] %d has taken a fork\n", time_diff(&start), args->id);
	pthread_mutex_lock(args->right_fork->mut);
	printf("[%0.4f] %d has taken a fork\n", time_diff(&start), args->id);
	args->philo_eat++;
	printf("[%0.4f] %d is eating\n", time_diff(&start), args->id);
	if (args->philo_eat >= eat)
		args->philo_death = 1;
	printf("[%0.4f] %d is sleeping\n", time_diff(&start), args->id);
	usleep(20);
	printf("[%0.4f] %d is thinking\n", time_diff(&start), args->id);
	pthread_mutex_unlock(args->left_fork->mut);
	pthread_mutex_unlock(args->right_fork->mut);

}

void	*waiter(t_pthred *args)
{
	printf("philo %d thinking\n", args->id);
	usleep(20);
}

void	*life_philo(void *args)
{
	t_pthred	*philo;

	philo = (t_pthred *)args;
	hander(philo);
}

t_fork	**init_fork(t_philo *data)
{
	t_fork	**tmp;
	int		i;

	i = 0;
	tmp = (t_fork **)malloc(sizeof(t_fork *) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		tmp[i] = (t_fork *)malloc(sizeof(t_fork));
		tmp[i]->id = i + 1;
		tmp[i]->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(tmp[i]->mut, NULL);
		i++;
	}
	data->forks = tmp;
}

t_pthred	**info_inicialize(t_philo *data)
{
	pthread_t	*th;
	t_pthred	**info;
	int			i;
	int			j;

	i = 0;
	j = 0;
	info = (t_pthred **)malloc(sizeof(t_pthred *) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		info[i] = (t_pthred *)malloc(sizeof(t_pthred));
		info[i]->id = i + 1;
		info[i]->philo_death = 0;
		info[i]->philo_eat = 0;
		info[i]->th = (pthread_t *)malloc(sizeof(pthread_t));
		info[i]->left_fork = data->forks[j];
		info[i]->right_fork = data->forks[j + 1];
		i++;
		//j++;
	}
	return (info);
}

int	death(t_philo *data)
{
	int		i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (data->info[i]->philo_death == 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_philo		philo;
	struct timeval	end;
	int		i;

	if (checker(argc, argv) == 1)
		return (1);
	parce(argv, &philo);
	init_fork(&philo);
	philo.info = info_inicialize(&philo);
	eat = philo.must_eat;
	eating = 0;
	gettimeofday(&start, NULL);
	while (1)
	{
		i = 0;
		while (i < philo.number_of_philosophers)
		{
			if (philo.info[i]->philo_death == 0)
			{
				if (pthread_create(philo.info[i]->th, NULL, &life_philo, philo.info[i]))
					return (1);
				pthread_detach(*(philo.info[i]->th));
			}
			i++;
		}
		if (death(&philo))
			break;
	}
	//pthread_mutex_destroy(&mut);
	return (0);
}