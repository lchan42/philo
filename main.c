/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:56:04 by lchan             #+#    #+#             */
/*   Updated: 2022/06/21 18:19:24 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void)
{
	printf("I M THE FIRST THREAD\n");
}

int	main (int ac, char **av)
{
	t_data		data;
	pthread_t	first_thread;

	if (__init_data(ac -1, av + 1, &data) == -1)
		return (-1);
	__visual_print_data(&data);
	if (pthread_create(&first_thread, NULL,(void *) &routine, NULL))
		printf ("error pthread\n");
	pthread_join(first_thread, NULL);
	return (0);
}
