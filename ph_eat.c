/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:11:03 by lchan             #+#    #+#             */
/*   Updated: 2022/08/18 17:41:57 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__waiting_to_eat(t_philo *philo, pthread_mutex_t *mutex)
{
	while (1)
	{
		if (philo->hp > 0 && mutex->__data.__lock == 0)
		{
			pthread_mutex_lock(mutex);
			__voice(philo, FORK_MESS);
			return (0);
		}
		else
		{
			philo->hp -= HP_LOSS;
			if (philo->hp <= 0)
			{
				__voice_of_death(philo);
				return (-1);
			}
			usleep(HP_LOSS - 50);
		}
	}
}

int	__pick_fork(t_philo *philo)
{
	if (philo->rgt == philo->lft)
	{
		__voice(philo, FORK_MESS);
		usleep(philo->hp);
		__voice_of_death(philo);
	}
	else if (__is_even_nbr(philo->id + 1))
	{
		__waiting_to_eat(philo, philo->lft);
		__waiting_to_eat(philo, philo->rgt);
		return (0);
	}
	else
	{
		__waiting_to_eat(philo, philo->rgt);
		__waiting_to_eat(philo, philo->lft);
		return (0);
	}
	return(-1);
}

void	__drop_fork(t_philo *philo)
{
	if (__is_even_nbr(philo->id + 1))
	{
		pthread_mutex_unlock(philo->lft);
		pthread_mutex_unlock(philo->rgt);
	}
	else
	{
		pthread_mutex_unlock(philo->rgt);
		pthread_mutex_unlock(philo->lft);
	}
}

int	__eat(t_philo *philo)
{
	int	ret;

	if (__pick_fork(philo))
		return (-1);
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
	return (ret);
}
