/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:03:35 by algabrie          #+#    #+#             */
/*   Updated: 2022/03/27 17:41:27 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *nptr)
{
	int	stg;
	int	signal;
	int	i;

	stg = 0;
	if (!nptr)
		return (0);
	i = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		signal = -1;
	else
		signal = 1;
	if (signal == -1 || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		stg = (stg * 10) + (nptr[i++] - '0');
	return (stg * signal);
}

unsigned long	time_from_start_in_ms(void)
{
	struct timeval			time;
	static unsigned long	start_time = 0;

	gettimeofday(&time, NULL);
	if (start_time == 0)
		start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start_time);
}
