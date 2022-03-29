/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:05:32 by algabrie          #+#    #+#             */
/*   Updated: 2022/03/28 21:06:18 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_philo(void *args)
{
	t_pthred	*philo;

	philo = (t_pthred *)args;
	if (philo->id % 2 == 0)
		usleep(50);
	philo_eat(philo);
	printf("[%ld] %d is sleeping\n", time_from_start_in_ms(), philo->id);
	usleep((philo->data->time_to_sleep * 1000) * 0.50);
	printf("[%ld] %d is thinking\n", time_from_start_in_ms(), philo->id);
	return (life_philo((void *)args));
}

void	init_fork(t_philo *data)
{
	t_fork	**tmp;
	int		i;

	i = 0;
	tmp = (t_fork **)malloc(sizeof(t_fork *)
			* (data->number_of_philosophers + 1));
	while (i < data->number_of_philosophers)
	{
		tmp[i] = (t_fork *)malloc(sizeof(t_fork));
		tmp[i]->id = i + 1;
		tmp[i]->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(tmp[i]->mut, NULL);
		i++;
	}
	tmp[i] = (t_fork *)malloc(sizeof(t_fork));
	tmp[i]->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_lock(tmp[i]->mut);
	data->forks = tmp;
}

t_pthred	**info_inicialize(t_philo *data)
{
	t_pthred	**info;
	int			i;
	int			j;

	i = 0;
	j = 0;
	info = (t_pthred **)malloc(sizeof(t_pthred *)
			* data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		info[i] = (t_pthred *)malloc(sizeof(t_pthred));
		info[i]->id = i + 1;
		info[i]->philo_death = 0;
		info[i]->time_eat = 0;
		info[i]->philo_eat = 0;
		info[i]->data = data;
		info[i]->th = (pthread_t *)malloc(sizeof(pthread_t));
		info[i]->left_fork = data->forks[j];
		info[i]->right_fork = data->forks[j + 1];
		i++;
		if (i < data->number_of_philosophers - 1)
			j++;
	}
	return (info);
}
