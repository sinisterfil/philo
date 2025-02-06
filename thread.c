/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 03:42:44 by hbayram           #+#    #+#             */
/*   Updated: 2025/02/06 16:21:13 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	to_be_or_not_to_be(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

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
	while (!to_be_or_not_to_be(philo))
	{
		feasting(philo);
		daydreaming(philo);
		overthinking(philo);
	}
	return (pointer);
}

int	mother_thread(t_philosophy *program, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, &to_be_or_not_to_be,
			program->philo) != 0)
		terminator(program, forks, "Thread creation error");
	i = 0;
	while (i < program->philo[0].num_of_philo)
	{
		if (pthread_create(&program->philo[i].thread, NULL,
				&philosophers_dilemma, &program->philo[i]) != 0)
			terminator(program, forks, "Thread creation error");
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		terminator(program, forks, "Thread join error");
	i = 0;
	while (i < program->philo[0].num_of_philo)
	{
		if (pthread_join(program->philo[i].thread, NULL) != NULL)
			terminator(program, forks, "Thread join error");
		i++;
	}
	return (0);
}
