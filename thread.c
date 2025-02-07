/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 03:42:44 by hbayram           #+#    #+#             */
/*   Updated: 2025/02/07 16:52:35 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	terminator(t_philosophy *program, pthread_mutex_t *forks, char *arg)
{
	int	i;

	i = 0;
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->philo[0].num_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	*philosophers_dilemma(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!(*philo->dead))
	{
		feasting(philo);
		dreaming(philo);
		overthinking(philo);
	}
	return (NULL);
}

int	mother_thread(t_philosophy *program, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, &to_be_or_not_to_be, program->philo) != 0)
		terminator(program, forks, "Thread creation error");
	i = 0;
	while (i < program->philo[0].num_of_philo)
	{
		if (pthread_create(&program->philo[i].thread, NULL,
				&philosophers_dilemma, &program->philo[i]) != 0)
			{
				terminator(program, forks, "Thread creation error");
				return (1);
			}
		i++;
	}
	i = 0;
	while (i < program->philo[0].num_of_philo)
	{
		if (pthread_join(program->philo[i].thread, NULL) != 0)
			terminator(program, forks, "Thread join error");
		i++;
	}
	return (0);
}
