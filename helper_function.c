/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:16:35 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/13 21:57:55 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_longatol(const char *str)
{
	long	result;
	int		index;
	int		sing;

	index = 0;
	sing = 1;
	result = 0;
	while (str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sing *= -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + (str[index] - '0');
		index++;
	}
	if (result > 2147483647 || result < -2147483648)
		return (-1);
	return (result * sing);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);	
}

void	ft_usleep(long time)
{
	long	start;
	start = get_current_time();
	while(get_current_time() - start < time)
	{
		usleep(100);
	}
}

void	ft_time(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->time_to_start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
