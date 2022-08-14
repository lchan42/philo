/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:31:08 by lchan             #+#    #+#             */
/*   Updated: 2022/08/14 12:46:48 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	*__routine(void *philo)
{
	if (!__is_even_nbr(((t_philo *)philo)->id))
		usleep(1000);
//	while (1)
//	{
		__eat((t_philo *)philo);
		//	__sleep((t_philo *)philo);
		//	__think((t_philo *)philo);
//	}









	//__hands_lock((t_philo *)philo);
	//__the_voice(philo);
	//printf("I M THE FIRST THREAD %d\n", ((t_philo *)philo)->id);
	//__hands_unlock((t_philo *)philo);
	return (philo);
}
/*
void	*__routine(void *philo)
{
//	if ((((t_philo *)philo)->id + 1 == ((t_philo *)philo)->data->philo_nbr))
//		usleep(1000);
	if (!__is_even_nbr(((t_philo *)philo)->id))
		usleep(1000);
	while (1)
		if (((t_philo *)philo)->rgt->__data.__lock == 0 && ((t_philo *)philo)->lft->__data.__lock == 0)
			break;
	// pthread_mutex_lock(((t_philo *)philo)->lft);
	// pthread_mutex_lock(((t_philo *)philo)->rgt);

	__hands_lock((t_philo *)philo);
	printf("I M THE FIRST THREAD %d\n", ((t_philo *)philo)->id);
	__hands_unlock((t_philo *)philo);
	// pthread_mutex_unlock(((t_philo *)philo)->lft);
	// pthread_mutex_unlock(((t_philo *)philo)->rgt);

	return (philo);
}
*/
 /*****
  * timestamp_in_ms X has taken a fork
  * timestamp_in_ms X is eating
  * timestamp_in_ms X is sleeping
  * timestamp_in_ms X is thinking
  * timestamp_in_ms X died
  * philo.rgt.__data.__lock
 ****/

