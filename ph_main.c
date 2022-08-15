/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:56:04 by lchan             #+#    #+#             */
/*   Updated: 2022/08/15 16:56:00 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__launch_philo(t_data *data, int nbr)
{
	int	i;

	i = -1;
	if (nbr)
	{
		while (++i < nbr)
			if(pthread_create(&((data->philo_tab[i]).ph_thread), \
			NULL,\
			&__routine, (void *)&data->philo_tab[i]))
				return (i);
	}

	return (0);
}

int	__join_philo(t_data *data, int nbr)
{
	int	i;

	i = -1;
	if (nbr)
		while (++i < nbr)
			pthread_join((data->philo_tab[i].ph_thread), NULL);
	return (0);
}

int	main (int ac, char **av)
{
	t_data		data;

	if (__init_data(ac -1, av + 1, &data) == -1)
		return (-1);
	if (__set_table(&data) == -1)
		return (-1);
//	__visual(&data, ALL);
	__launch_philo(&data, data.philo_nbr);
	__join_philo(&data, data.philo_nbr);
	__ultimate_free(&data);
	//printf("end of main process\n");
	return (0);
}


