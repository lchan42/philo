/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:54:34 by lchan             #+#    #+#             */
/*   Updated: 2022/08/14 19:50:48 by lchan            ###   ########.fr       */
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
		else
		{
			philo->hp--;
			if (philo->hp <= 0)
				__voice_of_death(philo);
			usleep(1);
		}
	}
}




/************************ voice *************************/
void	__voice_of_thefork(t_philo *philo)
{
	pthread_mutex_lock(philo->data->the_voice);
	if (philo->data->blood == 0)
		printf("%lld %d has taken a fork\n", __timestamp(philo, philo->prev_lunch), philo->id + 1);
	pthread_mutex_unlock(philo->data->the_voice);
}

void	__voice_of_death(t_philo *philo)
{
	pthread_mutex_lock(philo->data->the_voice);
	if (philo->data->blood == 0)
	{
		philo->data->blood++;
		printf("%lld %d died\n", __timestamp(philo, philo->watch), philo->id + 1);
	}
	pthread_mutex_unlock(philo->data->the_voice);
}

/************************ utils *************************/
long long	__timestamp(t_philo *philo, long long now)
{
	return (now - philo->data->start_time);
}

int	__aftermealstatus(t_philo *philo)
{
	if (philo->data->tteat >= philo->data->ttdie)
	{
		usleep(philo->data->ttdie);
		philo->watch = philo->prev_lunch + philo->data->ttdie;
		philo->status = DEAD;
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
	int	ret;

	__pick_fork(philo);
	__set_starting_time(&(philo->prev_lunch));
	__voice_of_thefork(philo);
	usleep(philo->data->tteat);
	__drop_fork(philo);
	ret = __aftermealstatus(philo);
	return (__aftermealstatus(philo));
	//return (-1);
}
