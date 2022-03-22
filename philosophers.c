#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	philo;

	if (checker(argc, argv) == 1)
		return (1);
	parce(argv, &philo);
	return (0);
}