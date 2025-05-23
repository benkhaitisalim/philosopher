/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsalim <bsalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:38:47 by bsalim            #+#    #+#             */
/*   Updated: 2025/05/23 20:29:43 by bsalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
    if (ac != 5) {
        printf("Error: Incorrect number of arguments.\n");
        return 1;
    }
    t_data *data = malloc(sizeof(t_data));
    if (!data) {
        printf("Error: Memory allocation for `data` failed.\n");
        return 1;
    }

    if (parsing(data, av) == -1) {
        printf("Error: Invalid input detected.\n");
        free_pthread(data);
        free(data);
        return 1;
    }
    if (initialization_struct(data) == -1) {
        printf("Error: Memory allocation failed during initialization.\n");
        free(data);
        return 1;
    }
    if(create_thread(data) == -1)
    {
        return 1;
    }
    if(join_pthread(data) == -1)
    {
        return 1;
    }
    // stop_simulation(data);
    free_pthread(data);
    
    return 0;
}
