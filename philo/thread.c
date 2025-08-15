/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 03:42:44 by hbayram           #+#    #+#             */
/*   Updated: 2025/08/01 14:34:04 by hbayram          ###   ########.fr       */
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

void	feasting2(t_philo *philo)
{
	if(philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, philo->id, "has taken a fork");
		if (philo->num_of_philo == 1)
		{
			ft_usleep(philo->time_to_die);
			pthread_mutex_unlock(philo->left_fork);
			return ;
		}
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, philo->id, "has taken a fork");
	}
	else 
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, philo->id, "has taken a fork");
		if (philo->num_of_philo == 1)
		{
			ft_usleep(philo->time_to_die);
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, philo->id, "has taken a fork");
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	print_message(philo, philo->id, "is eating");
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philosophers_dilemma(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	print_message(philo, philo->id, "is thinking");
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		if(philo->num_of_philo % 2 == 1)
			feasting(philo);
		else
			feasting2(philo);
		dreaming(philo);
		overthinking(philo);
		pthread_mutex_lock(philo->dead_lock);
		if ((*philo->dead))
		{
			pthread_mutex_unlock(philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philo->dead_lock);
	}
	return (NULL);
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
		{
			terminator(program, forks, "Thread creation error");
			return (1);
		}
		i++;
	}
	i = -1;
	while (++i < program->philo[0].num_of_philo)
	{
		if (pthread_join(program->philo[i].thread, NULL) != 0)
			terminator(program, forks, "Thread join error");
	}
	pthread_join(monitor, NULL);
	return (0);
}
