/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:56:04 by lchan             #+#    #+#             */
/*   Updated: 2022/08/13 12:13:44 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main (int ac, char **av)
{
	t_data		data;
	//t_philo		philo;
	//pthread_t	first_thread;

	if (__init_data(ac -1, av + 1, &data) == -1)
		return (-1);
	if (__set_table(&data) == -1)
		return (-1);
	__visual_print_data(&data);
	__table_free(&data);
	printf("end of main process\n");
	//free all
	//if (__init_philo() == -1)
	//	return (-1);

	// if (pthread_create(&first_thread, NULL,(void *) &routine, NULL))
	// 	printf ("error pthread\n");
	//pthread_join(first_thread, NULL);
	return (0);
}
