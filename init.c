/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:35:04 by hbayram           #+#    #+#             */
/*   Updated: 2025/02/12 12:31:38 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	input_init(t_philo *philo, char **av)
{
	philo->num_of_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->num_to_eat = ft_atoi(av[5]);
	else
		philo->num_to_eat = -1;
}

void	program_init(t_philosophy *program, t_philo *philo)
{
	program->dead_flag = 0;
	program->philo = philo;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
}

void	philos_init(t_philosophy *program, t_philo *philo,
		pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		input_init(&philo[i], av);
		philo[i].start_time = get_time();
		philo[i].last_meal = get_time();
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].write_lock = &program->write_lock;
		philo[i].dead = &program->dead_flag;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % ft_atoi(av[1])];
		i++;
	}
}

void	forks_init(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
