/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:12:03 by hbayram           #+#    #+#             */
/*   Updated: 2025/02/06 17:40:22 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int full_belly(void)
{

}

int if_dead(t_philo *philo, size_t time_to_die)
{
    pthread_mutex_lock(philo->meal_lock);
    if(get_time() - philo->last_meal >= time_to_die && philo->eating == 0)
    {
        pthread_mutex_unlock(philo->meal_lock);
        return(1);
    }
    pthread_mutex_unlock(philo->meal_lock);
    return (0);
}

int anyone_reach_nirvana(void)
{
    if (philosopher_dead(&philo[i], philo[i].time_to_die))
        {
            print_message("died", &philo[i], philo[i].id);
            pthread_mutex_lock(philo[0].dead_lock);
            *philo->dead = 1;
            pthread_mutex_unlock(philo[0].dead_lock);
            return (1);
        }
}
