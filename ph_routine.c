/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:31:08 by lchan             #+#    #+#             */
/*   Updated: 2022/08/13 21:52:54 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*__routine(void *philo)
{
	//if (__is_even_nbr(((t_philo *)philo)->id))
	//	usleep(1000);
	while (1)
		if (((t_philo *)philo)->rgt->__data.__lock == 0 && ((t_philo *)philo)->lft->__data.__lock == 0)
			break;
	pthread_mutex_lock(((t_philo *)philo)->rgt);
	pthread_mutex_lock(((t_philo *)philo)->lft);
	printf("I M THE FIRST THREAD %d\n", ((t_philo *)philo)->id);
	pthread_mutex_unlock(((t_philo *)philo)->rgt);
	pthread_mutex_unlock(((t_philo *)philo)->lft);
	return (philo);
}

 /*****
  * timestamp_in_ms X has taken a fork
  * timestamp_in_ms X is eating
  * timestamp_in_ms X is sleeping
  * timestamp_in_ms X is thinking
  * timestamp_in_ms X died
  * philo.rgt.__data.__lock
 ****/

