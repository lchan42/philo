/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_set_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:05:45 by luc_chan          #+#    #+#             */
/*   Updated: 2022/08/13 13:12:27 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	__init_mutex(t_data *data, int nbr)
{
	while (nbr--)
		if (pthread_mutex_init(&(data->table_set[nbr]), NULL))
			return (-1);
	// while (nbr--)
	// 	printf("init mutex ret = %d\n", pthread_mutex_init(&(data->table_set[nbr]), NULL));
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

int	__set_philo(t_data *data, t_philo *philo, int index)
{
	int	i;

	if (index == data->philo_nbr - 1)
		i = data->philo_nbr;
	else
		i = index + 1;
	philo->id = index + 1;
	philo->status = ALIVE;
	philo->prev_lunch = 0;
	philo->rgt = data->table_set + index;
	philo->lft = data->table_set + i;
	philo->data = data;
	return (0);
}

int	__init_philo(t_data *data, int nbr)
{
	int	index;

	index = -1;
	data->philo_tab = malloc(sizeof(pthread_t) * nbr);
	if (!data->philo_tab)
		return (-1);
	while (++index < nbr)
		if (__set_philo(data, data->philo_tab + index, index) == -1)
			return (-1);
	return (0);
}

int	__set_table(t_data *data)
{
	int	i;
	int	((*__set_table[INIT_SIZE])(t_data *data, int nbr));

	__set_table[0] = &__init_table;
	__set_table[1] = &__init_mutex;
	__set_table[2] = &__init_philo;

	i = 0;
	while (i < INIT_SIZE)
	{
		if (__set_table[i](data, data->philo_nbr) == -1)
			return (i);
		i++;
	}
	return (0);
}
