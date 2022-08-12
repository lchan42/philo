/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luc_chan <luc_chan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:21:16 by luc_chan          #+#    #+#             */
/*   Updated: 2022/08/12 13:24:12 by luc_chan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__table_free(t_data *data)
{
	//int				tmp;
	pthread_mutex_t	*end_limit;
	pthread_mutex_t	*start_limit;

	if (data && data->table_set)
	{
		//tmp = data->philo_nbr;
		start_limit = data->table_set;
		end_limit = data->table_set + data->philo_nbr;
		//while (tmp)
		//	pthread_mutex_destroy(&(data->table_set[tmp--]));
		while (start_limit < end_limit)
			printf("destroying mutex ret = %d\n", pthread_mutex_destroy((start_limit++)));
		free(data->table_set);
		data->table_set = NULL;
	}
}
