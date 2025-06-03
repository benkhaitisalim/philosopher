/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:38:47 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/03 17:29:22 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_rotine_on_or_more(t_data *data)
{
	if (create_thread(data) == -1)
		return (-1);
	if (join_pthread(data) == -1)
		return (-1);
	free_pthread(data);
	return (0);
}

int	check_arg_ac_allocation_data(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("arguments not okey .\n");
		return (-1);
	}
	return (1);
}

int	check_parsing(t_data *data, int ac, char **av)
{
	if (parsing(data, av, ac) == -1)
	{
		printf("Invalid input .\n");
		free(data);
		return (-1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data) 
	{
		printf("memory allocation for  failed.\n");
		return (-1);
	}
	memset(data, 0, sizeof(t_data));
	if (check_arg_ac_allocation_data(ac) == -1
		|| check_parsing(data, ac, av) == -1)
		return (-1);
	if (initialization_struct_part1(data) == -1 || init_philos(data) == -1
		|| init_pthread_mutex(data) == -1
		|| initialization_struct_part2(data) == -1)
		return (-1);
	if (philo_rotine_on_or_more(data) == -1)
		return (-1);
	return (0);
}
