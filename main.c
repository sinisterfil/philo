/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:38:49 by hbayram           #+#    #+#             */
/*   Updated: 2025/02/04 23:30:00 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_rules(void)
{
	printf("\n");
	printf(" +---------------- Let me help you! -----------------+\n");
	printf(" |                                                   |\n");
	printf(" |      Usage: ./philo 5 800 200 200 [7]             |\n");
	printf(" |                                                   |\n");
	printf(" |------------------- IMPORTANT ---------------------|\n");
	printf(" |                                                   |\n");
	printf(" | Philo number must be >0 && <200                   |\n");
	printf(" |                                                   |\n");
	printf(" | All arguments must be number >0                   |\n");
	printf(" |                                                   |\n");
	printf(" | Number of times each philosopher                  |\n");
	printf(" |           must eat is an optional argument.       |\n");
	printf(" |                                                   |\n");
	printf(" +---------------------------------------------------+\n");
	printf("\n");
}

static int	check_content(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	check_av(int ac, char **av)
{
	int	i;

	i = 1;
	if (ft_atoi(av[i]) > MAX_PHILO || ft_atoi(av[i]) <= 0
		|| check_content(av[i]) == 1)
		ft_rules();
	i++;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0 || check_content(av[i]) == 1)
			ft_rules();
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philosophy program;
	t_philo philo[MAX_PHILO];
	pthread_mutex_t forks[MAX_PHILO];

	if (ac != 5 && ac != 6)
	{
		ft_rules();
		return (1);
	}
	if (check_av(ac, av) != 0)
		return (1);
    program_init(&program, philo);
	forks_init(forks, ft_atoi(av[1]));
	philos_init(philo, &program, forks, av);
}