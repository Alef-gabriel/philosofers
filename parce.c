/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:05:26 by algabrie          #+#    #+#             */
/*   Updated: 2022/03/28 16:19:19 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parce(char **argv, t_philo *st)
{
	st->number_of_philosophers = ft_atoi(argv[1]);
	st->time_to_die = ft_atoi(argv[2]);
	st->time_to_eat = ft_atoi(argv[3]);
	st->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		st->must_eat = ft_atoi(argv[5]);
		if (st->must_eat < 0)
			st->must_eat = 0;
	}
	else
		st->must_eat = -1;
	return (0);
}
