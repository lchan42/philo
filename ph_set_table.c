/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_set_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luc_chan <luc_chan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:05:45 by luc_chan          #+#    #+#             */
/*   Updated: 2022/08/12 13:20:41 by luc_chan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	__init_mutex(t_data *data, int nbr)
{
	// while (nbr--)
	// 	if (pthread_mutex_init(&(data->table_set[nbr]), NULL))
	// 		return (-1);
	while (nbr--)
		printf("init mutex ret = %d\n", pthread_mutex_init(&(data->table_set[nbr]), NULL));
	return (0);
}

int	__init_table(t_data *data, int nbr)
{
	if (!nbr)
		return (-1);
	data->table_set = malloc(sizeof(pthread_mutex_t) * nbr);
	if (!data->table_set)
		return (-1);
	else
		printf("in ph_set_table.c : table has been set\n");
	return (0);
}

int	__set_table(t_data *data)
{
	int	i;
	int	((*__set_table[INIT_SIZE])(t_data *data, int nbr));

	__set_table[0] = &__init_table;
	__set_table[1] = &__init_mutex;

	i = 0;
	while (i < INIT_SIZE)
	{
		if (__set_table[i](data, data->philo_nbr) == -1)
			return (i);
		i++;
	}
	return (0);
}

