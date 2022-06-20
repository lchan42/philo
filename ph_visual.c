/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_visual.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:13:06 by lchan             #+#    #+#             */
/*   Updated: 2022/06/20 17:37:46 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__visual_print_data(t_data *data)
{
	printf("nbr philo %d\n", data->philo_nbr);
	printf("time to die %d\n", data->ttdie);
	printf("time to sleep %d\n", data->ttsleep);
	printf("time to eat %d\n", data->tteat);
	printf("eat requirement %d\n", data->eat_rqrmt);
	printf("start time %lld\n", data->start_time);
}
