/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:05:38 by algabrie          #+#    #+#             */
/*   Updated: 2022/03/26 22:05:39 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	checker_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("error : invalid number in arguments\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	checker(int argc, char **argv)
{
	if (argc > 6)
	{
		printf("error : too many arguments\n");
		return (1);
	}
	else if (argc < 6)
	{
		printf("error : invalid arguments\n");
		return (1);
	}
	else if (checker_digit(argv) == 1)
		return (1);
	return (0);
}
