/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:54:34 by lchan             #+#    #+#             */
/*   Updated: 2022/08/14 21:19:22 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__waiting_list(t_philo *philo)
{
	while (1)
	{
		if (((t_philo *)philo)->rgt->__data.__lock == 0 && ((t_philo *)philo)->lft->__data.__lock == 0)
			return (0);
		else
		{
			philo->hp--;
			if (philo->hp <= 0)
			{
				__voice_of_death(philo);
				return (1) ;
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


/************************ voice *************************/
void	__voice_of_thefork(t_philo *philo)
{
	pthread_mutex_lock(philo->data->the_voice);
	if (philo->data->blood == 0)
	{
		philo->prev_lunch = (philo->data->ttdie * 1000 - philo->hp) + philo->watch;
		printf("%lld %d has taken a fork\n",
		__voice_time(philo->data->start_time, __get_time()), philo->id + 1);
	}
	pthread_mutex_unlock(philo->data->the_voice);
}

void	__voice_of_death(t_philo *philo)
{
	pthread_mutex_lock(philo->data->the_voice);
	if (philo->data->blood == 0)
	{
		philo->data->blood++;
		philo->status = DEAD;
		printf("%lld %d died\n", __voice_time(philo->data->start_time, __get_time()), philo->id + 1);
	}
	pthread_mutex_unlock(philo->data->the_voice);
}

/************************ utils *************************/
long long	__timestamp(t_philo *philo, long long now)
{
	return (now - philo->data->start_time);
}

long long	__get_time()
{
	struct timeval	c_time;

	if (gettimeofday(&c_time, NULL) == -1)
		return (-1);
	else
		return (c_time.tv_sec *1000 + c_time.tv_usec / 1000);
}

long long	__voice_time(long long start, long long now)
{
	return (now - start);
}

int	__aftermealstatus(t_philo *philo)
{
	if (philo->data->tteat * 1000 >= (int)philo->hp)
	{
		usleep(philo->hp);
		philo->status = DEAD;
		__voice_of_death(philo);
		return (-1);
	}
	else
	{
		philo->hp -= philo->data->ttdie;
		usleep(philo->data->tteat);
		philo->nbr_meal++;
		return 0;
	}
}

/************************ eat main *************************/
int	__eat(t_philo *philo)
{
	int	ret;

	__set_starting_time(&(philo->watch));
	if (__waiting_list(philo))
		return (-1);
	__pick_fork(philo);
	__voice_of_thefork(philo);
	ret = __aftermealstatus(philo);
	__drop_fork(philo);
	return (ret);
}
