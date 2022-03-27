/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:37:11 by algabrie          #+#    #+#             */
/*   Updated: 2022/03/27 14:57:27 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clear_struct(t_philo *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(data->forks[i]->mut);
		free(data->forks[i]->mut);
		free(data->forks[i]);
		free(data->info[i]->th);
		free(data->info[i]->eat_time);
		free(data->info[i]);
		i++;
	}
	free(data->forks);
	free(data->start);
	free(data->info);
}
