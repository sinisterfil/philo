/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbayram <hbayram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:40:01 by hbayram           #+#    #+#             */
/*   Updated: 2025/02/05 09:35:02 by hbayram          ###   ########.fr       */
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

size_t get_time(void)
{
	size_t			current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}
