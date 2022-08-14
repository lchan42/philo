/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:54:34 by lchan             #+#    #+#             */
/*   Updated: 2022/08/14 12:46:17 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__pick_fork(t_philo *philo)
{
	if (__is_even_nbr(((t_philo *)philo)->id))
	{
		pthread_mutex_lock(((t_philo *)philo)->lft);
		pthread_mutex_lock(((t_philo *)philo)->rgt);
	}
	else
	{
		pthread_mutex_lock(((t_philo *)philo)->rgt);
		pthread_mutex_lock(((t_philo *)philo)->lft);
	}
}

void	__drop_fork(t_philo *philo)
{
	if (__is_even_nbr(((t_philo *)philo)->id))
	{
		pthread_mutex_unlock(((t_philo *)philo)->lft);
		pthread_mutex_unlock(((t_philo *)philo)->rgt);
	}
	else
	{
		pthread_mutex_unlock(((t_philo *)philo)->rgt);
		pthread_mutex_unlock(((t_philo *)philo)->lft);
	}
}

void	__waiting_list(t_philo *philo)
{
	while (1)
	{
		if (((t_philo *)philo)->rgt->__data.__lock == 1 && ((t_philo *)philo)->lft->__data.__lock == 1)
			break;
	}
}

void	__voice_of_thefork(t_philo *philo)
{
	//	__waiting_list(philo);
	pthread_mutex_lock(philo->data->the_voice);
	printf("%d has taken a fork\n", philo->id + 1);
	pthread_mutex_unlock(philo->data->the_voice);
}

void	__voice_of_death(t_philo *philo)
{
	//	__waiting_list(philo);
	pthread_mutex_lock(philo->data->the_voice);
	printf("%d died\n", philo->id + 1);
	pthread_mutex_unlock(philo->data->the_voice);
}

void	__eat(t_philo *philo)
{
	__pick_fork(philo);
	__voice_of_thefork(philo);
	__drop_fork(philo);
	if (philo->data->tteat <= philo->data->ttdie)
	{
		usleep(philo->data->ttdie);
		__voice_of_death(philo);
	}
	else
		usleep(philo->data->tteat);
}






