/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:05:32 by algabrie          #+#    #+#             */
/*   Updated: 2022/03/26 22:13:37 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*life_philo(void *args)
{
	t_pthred	*philo;

	philo = (t_pthred *)args;
	while (!philo->philo_death)
	{
		philo_eat(philo);
		printf("[%d] %d is sleeping\n", (int)(time_diff(philo->data->start) * 1000), philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		printf("[%d] %d is thinking\n", (int)(time_diff(philo->data->start) * 1000), philo->id);
	}
	return ((void *)args);
}

void	init_fork(t_philo *data)
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
		if (i < data->number_of_philosophers - 1)
			j++;
	}
	return (info);
}
