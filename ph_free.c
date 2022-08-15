/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:21:16 by luc_chan          #+#    #+#             */
/*   Updated: 2022/08/15 15:13:54 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__table_free(t_data *data)
{
	pthread_mutex_t	*end_limit;
	pthread_mutex_t	*start_limit;

	if (data && data->table_set)
	{
		start_limit = data->table_set;
		end_limit = data->table_set + data->philo_nbr;
		while (start_limit < end_limit)
			pthread_mutex_destroy((start_limit++));
		free(data->table_set);
		data->table_set = NULL;
	}
}

void	__philo_free(t_data *data)
{
	if (data && data->philo_tab)
		free(data->philo_tab);
}

void	__free_setnull(void **malloc_elem)
{
	if (malloc_elem && *malloc_elem)
	{
		free (*malloc_elem);
		*malloc_elem = NULL;
	}
}

void	__ultimate_free(t_data *data)
{
	int	index;

	index = -1;
	void ((*__free_funk[FREE_FUNK])(t_data *data));

	__free_funk[0] = &__table_free;
	__free_funk[1] = &__philo_free;
	while (++index < FREE_FUNK)
		__free_funk[index](data);
}
