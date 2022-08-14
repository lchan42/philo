/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:54:34 by lchan             #+#    #+#             */
/*   Updated: 2022/08/14 13:34:52 by lchan            ###   ########.fr       */
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







/************************ voice *************************/
void	__voice_of_thefork(t_philo *philo)
{
	pthread_mutex_lock(philo->data->the_voice);
	printf("%lld %d has taken a fork\n", philo->prev_lunch, philo->id + 1);
	pthread_mutex_unlock(philo->data->the_voice);
}

void	__voice_of_death(t_philo *philo)
{
	long long	the_time;

	__set_starting_time(&the_time);
	pthread_mutex_lock(philo->data->the_voice);
	printf("%lld %d died\n", the_time, philo->id + 1);
	philo->data->blood++;
	pthread_mutex_unlock(philo->data->the_voice);
}



/************************ utils *************************/

int	__check_of_death(t_philo *philo)
{
	if (philo->data->tteat >= philo->data->ttdie)
	{
		usleep(philo->data->ttdie);
		__voice_of_death(philo);
		return (-1);
	}
	else
	{
		usleep(philo->data->tteat);
		philo->nbr_meal++;
		return 0;
	}
}



/************************ eat main *************************/
int	__eat(t_philo *philo)
{
	if (philo->data->blood == 0)
	{
		__set_starting_time(&(philo->prev_lunch));
		__pick_fork(philo);
		__voice_of_thefork(philo);
		__drop_fork(philo);
		return (__check_of_death(philo));
	}
	return (-1);
}






