/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:05:21 by algabrie          #+#    #+#             */
/*   Updated: 2022/03/26 23:45:28 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_eat(t_pthred *args)
{
	pthread_mutex_lock(args->left_fork->mut);
	printf("[%d] %d has taken a fork\n", (int)(time_diff(args->data->start) * 1000), args->id);
	pthread_mutex_lock(args->right_fork->mut);
	printf("[%d] %d has taken a fork\n", (int)(time_diff(args->data->start) * 1000), args->id);
	args->philo_eat++;
	gettimeofday(args->eat_time, NULL);
	printf("[%d] %d is eating\n", (int)(time_diff(args->data->start) * 1000), args->id);
	usleep(args->data->time_to_eat * 1000);
	pthread_mutex_unlock(args->left_fork->mut);
	pthread_mutex_unlock(args->right_fork->mut);
	return ((void *)args);

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
			if (data->info[i]->philo_eat && (int)time_diff(data->info[i]->eat_time) * 1000 > data->time_to_die)
			{
				printf("[%d] %d died\n", (int)(time_diff(data->start) * 1000), data->info[i]->id);
				return (1);
			}
			if (data->info[i]->philo_eat >= data->must_eat)
				data->info[i]->philo_death = 1;
			if (data->info[i]->philo_death == 0)
				break ;
			i++;
		}
		if (i == data->number_of_philosophers)
			all_philo_death = 1;
	}
	return (0);
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
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;

	if (checker(argc, argv) == 1)
		return (1);
	parce(argv, &philo);
	init_fork(&philo);
	philo.info = info_inicialize(&philo);
	start_simulation(&philo);
	monitoring(&philo);
	clear_struct(&philo);
	return (0);
}