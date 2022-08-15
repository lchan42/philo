/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:54:34 by lchan             #+#    #+#             */
/*   Updated: 2022/08/15 17:01:22 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__waiting_to_speak(t_philo *philo)
{
	while (1)
	{
		if (((t_philo *)philo)->data->the_voice->__data.__lock == 0)
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

int	__lifestatus(t_philo *philo, int time_to)
{
	if (time_to * 1000 >= (int)philo->hp)
	{
		usleep(philo->hp);
		philo->status = DEAD;
		__voice_of_death(philo);
		return (-1);
	}
	else
	{
		philo->hp -= time_to /** 1000*/;
		usleep(time_to);
		return 0;
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

void	__voice_of_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->data->the_voice);
	if (philo->data->blood == 0)
	{
		printf("%lld %d is sleeping\n",
		__voice_time(philo->data->start_time, __get_time()), philo->id + 1);
	}
	pthread_mutex_unlock(philo->data->the_voice);
}

void	__voice_of_think(t_philo *philo)
{
	pthread_mutex_lock(philo->data->the_voice);
	if (philo->data->blood == 0)
	{
		printf("%lld %d is thinking\n",
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

// int	__lifestatus(t_philo *philo, int time_to)
// {
// 	if (philo->data->tteat * 1000 >= (int)philo->hp)
// 	{
// 		usleep(philo->hp);
// 		philo->status = DEAD;
// 		__voice_of_death(philo);
// 		return (-1);
// 	}
// 	else
// 	{
// 		philo->hp -= philo->data->ttdie;
// 		usleep(philo->data->tteat);
// 		return 0;
// 	}
// }
