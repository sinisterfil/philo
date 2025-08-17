/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:40:01 by hbayram           #+#    #+#             */
/*   Updated: 2025/08/17 17:15:08 by hbayram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

void	print_message(t_philo *philo, int id, char *message)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->dead_lock);
	if (!(*philo->dead))
		printf("%zu %d %s\n", time, id, message);
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_unlock(philo->write_lock);
}

size_t	get_time(void)
{
	size_t			current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

void	ft_usleep(t_philo *philo, size_t milliseconds)
{
	size_t	current;

	current = get_time();
	while ((get_time() - current) < milliseconds)
	{
		pthread_mutex_lock(philo[0].dead_lock);
        if (*philo->dead)
        {
            pthread_mutex_unlock(philo[0].dead_lock);
            break;
        }
        pthread_mutex_unlock(philo[0].dead_lock);
		usleep(500);
	}
}
