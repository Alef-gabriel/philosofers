#include "philo.h"

void	*philo_eat(t_pthred *args)
{
	pthread_mutex_lock(args->left_fork->mut);
	printf("[%0.3f] %d has taken a fork\n", time_diff(args->data->start), args->id);
	pthread_mutex_lock(args->right_fork->mut);
	printf("[%0.3f] %d has taken a fork\n", time_diff(args->data->start), args->id);
	args->philo_eat++;
	gettimeofday(args->eat_time, NULL);
	printf("[%0.3f] %d is eating\n", time_diff(args->data->start), args->id);
	usleep(args->data->time_to_eat);
	pthread_mutex_unlock(args->left_fork->mut);
	pthread_mutex_unlock(args->right_fork->mut);

}

void	*life_philo(void *args)
{
	t_pthred	*philo;

	philo = (t_pthred *)args;
	while (!philo->philo_death)
	{
		philo_eat(philo);
		printf("[%0.3f] %d is sleeping\n", time_diff(philo->data->start), philo->id);
		usleep(philo->data->time_to_sleep);
		printf("[%0.3f] %d is thinking\n", time_diff(philo->data->start), philo->id);
	}
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
		info[i]->eat_time = (struct timeval *)malloc(sizeof(struct timeval));
		info[i]->philo_eat = 0;
		info[i]->data = data;
		info[i]->th = (pthread_t *)malloc(sizeof(pthread_t));
		info[i]->left_fork = data->forks[j];
		info[i]->right_fork = data->forks[j + 1];
		i++;
		//j++;
	}
	return (info);
}

int	monitoring(t_philo *data)
{
	int	i;
	int	all_philo_death;

	all_philo_death = 0;
	while (!all_philo_death)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			if (data->info[i]->philo_eat && time_diff(data->info[i]->eat_time) > (float)data->time_to_die / 1000)
			{
				printf("philo die\n");
				exit(0);
			}
			if (data->must_eat == data->info[i]->philo_eat)
				data->info[i]->philo_death = 1;
			if (data->info[i]->philo_death == 0)
				break ;
			i++;
		}
		if (i == data->number_of_philosophers)
			all_philo_death = 1;
	}
}

int	start_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	gettimeofday(philo->start, NULL);
	while (i < philo->number_of_philosophers)
	{
		if (pthread_create(philo->info[i]->th, NULL, &life_philo, philo->info[i]))
			return (1);
		pthread_detach(*(philo->info[i]->th));
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo			philo;
	struct timeval	end;

	if (checker(argc, argv) == 1)
		return (1);
	parce(argv, &philo);
	init_fork(&philo);
	philo.info = info_inicialize(&philo);
	start_simulation(&philo);
	monitoring(&philo);
	//pthread_mutex_destroy(&mut);
	return (0);
}