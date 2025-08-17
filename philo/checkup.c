/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:12:03 by hbayram           #+#    #+#             */
/*   Updated: 2025/08/15 19:00:41 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	full_belly(t_philo *philo)
{
	int	full;
	int	i;

	i = 0;
	full = 0;
	if (philo[0].num_to_eat == -1)
		return (0);
	while (i < philo[0].num_of_philo)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].num_to_eat <= philo[i].meals_eaten)
			full++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (full == philo[0].num_of_philo)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

int	if_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal >= time_to_die && philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	anyone_reach_nirvana(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philo)
	{
		if (if_dead(&philo[i], philo[i].time_to_die))
		{
			print_message(&philo[i], philo[i].id, "died");
			pthread_mutex_lock(philo[i].dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(philo[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*to_be_or_not_to_be(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		if (anyone_reach_nirvana(philo) == 1 || full_belly(philo) == 1)
			break ;
	}
	return (0);
}
