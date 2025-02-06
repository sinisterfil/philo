/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:40:01 by hbayram           #+#    #+#             */
/*   Updated: 2025/02/06 17:40:42 by hbayram          ###   ########.fr       */
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
	int	i;
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

void	print_message(char *message, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!to_be_or_not_to_be(philo))
		printf("%zu %d %s\n", time, id, message);
	pthread_mutex_unlock(philo->write_lock);
}

size_t get_time(void)
{
	size_t			current_time;
	struct timeval	tv;  

	gettimeofday(&tv, NULL);//null saat dilimi 
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000); //tv_usec son saniyenin içinde geçen mikro saniye
	return (current_time); //tv_sec 1970ten beri geçen saniye 
}

int	ft_usleep(size_t milliseconds) //usleep mikro saniye alıyor
{
	size_t	clock;

	clock = get_time();
	while ((get_time() - clock) < milliseconds)
		usleep(500); //daha kesin süre beklemek içim
	return (0);
}
