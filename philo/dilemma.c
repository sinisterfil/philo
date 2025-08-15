/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dilemma.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 04:14:28 by hbayram           #+#    #+#             */
/*   Updated: 2025/08/15 16:34:10 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	overthinking(t_philo *philo)
{
	print_message(philo, philo->id, "is thinking");
}

void	dreaming(t_philo *philo)
{
	print_message(philo, philo->id, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	feasting(t_philo *philo)
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
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	print_message(philo, philo->id, "is eating");
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
