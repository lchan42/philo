/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_visual.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luc_chan <luc_chan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:13:06 by lchan             #+#    #+#             */
/*   Updated: 2022/08/12 13:23:06 by luc_chan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__visual_print_data(t_data *data)
{
	printf("nbr_philo:		%d\n", data->philo_nbr);
	printf("time_to_die:		%d\n", data->ttdie);
	printf("time_to_sleep:		%d\n", data->ttsleep);
	printf("time_to_eat: 		%d\n", data->tteat);
	printf("eat_requirement:	%d\n", data->eat_rqrmt);
	printf("start+time:		%lld\n", data->start_time);
	printf("table_set:		%p\n", data->table_set);
}
