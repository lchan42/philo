/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:11:03 by lchan             #+#    #+#             */
/*   Updated: 2022/08/15 20:04:34 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__waiting_to_eat(t_philo *philo)
{
	if (philo->rgt == philo->lft)
	{
		usleep(philo->data->ttdie - 100);
		__voice_of_death(philo);
		return (-1) ;
	}
	while (1)
	{
		if (philo->rgt->__data.__lock == 0
			&& philo->lft->__data.__lock == 0)
			return (0);
		else
		{
			philo->hp--;
			if (philo->hp <= 0)
			{
				__voice_of_death(philo);
				return (-1) ;
			}
			usleep(1000);
		}
	}
}

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
	__voice_of_thefork(philo);
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

// void	__set_nbr_meal(t_philo *philo)
// {
// 	philo->nbr_meal++;
// 	pthread_mutex_lock(philo->data->the_voice);
// 	if (philo->data->blood_switch == 0)
// 	{
// 		philo->prev_lunch = (philo->data->ttdie * 1000 - philo->hp) + philo->watch;
// 		printf("%07lld %d is eating\n",
// 		__voice_time(philo->data->start_time, __get_time()), philo->id + 1);
// 	}
// 	pthread_mutex_unlock(philo->data->the_voice);
// }

int	__eat(t_philo *philo)
{
	int	ret;

	__set_starting_time(&(philo->watch));
	if (__waiting_to_eat(philo))
		return (-1);
	__pick_fork(philo);
	__voice_of_meal(philo);
	ret = __lifestatus(philo, philo->data->tteat);
	if (ret == 0)
		//__set_nbr_meal(philo);
		philo->nbr_meal++;
	__drop_fork(philo);
	((t_philo *)philo)->hp = ((t_philo *)philo)->data->ttdie * 1000;
	return (ret);
}
