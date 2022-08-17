/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:11:03 by lchan             #+#    #+#             */
/*   Updated: 2022/08/17 11:28:07 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__waiting_to_eat(t_philo *philo)
{
	if (philo->rgt == philo->lft)
	{
		usleep(philo->hp);
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
			philo->hp -= 1000;
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
	__voice(philo, FORK_MESS);
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

int	__eat(t_philo *philo)
{
	int	ret;

	if (__waiting_to_eat(philo))
		return (-1);
	__pick_fork(philo);
	if (__voice(philo, EAT_MESS) == -1)
	{
		__drop_fork(philo);
		return (-1);
	}
	((t_philo *)philo)->hp = ((t_philo *)philo)->data->ttdie * 1000;
	ret = __lifestatus(philo, philo->data->tteat);
	if (ret == 0)
		philo->nbr_meal++;
	__drop_fork(philo);
	printf("philo-> %d ret is %d\n", philo->id + 1, ret);
	return (ret);
}
