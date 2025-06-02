/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:38:47 by bsalim            #+#    #+#             */
/*   Updated: 2025/06/02 16:25:41 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_rotine_on_or_more(t_data *data)
{
	if (one_philo_rotine(data) == -1)
		return (-1);
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
		printf("Error: Incorrect number of arguments.\n");
		return (-1);
	}
	return (1);
}

int	check_parsing(t_data *data, int ac, char **av)
{
	if (parsing(data, av, ac) == -1)
	{
		printf("Error: Invalid input detected.\n");
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
		printf("Error: Memory allocation for `data` failed.\n");
		return (-1);
	}
	if (check_arg_ac_allocation_data(ac) == -1
		|| check_parsing(data, ac, av) == -1)
		return (-1);
	if (initialization_struct_part1(data) == -1 || init_philos(data) == -1
		|| init_pthread_mutex(data) == -1
		|| initialization_struct_part2(data) == -1)
	{
		printf("Error: Memory allocation failed during initialization.\n");
		return (-1);
	}
	if (philo_rotine_on_or_more(data) == -1)
		return (-1);
	return (0);
}
