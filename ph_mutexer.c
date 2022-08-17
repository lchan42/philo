/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:54:34 by lchan             #+#    #+#             */
/*   Updated: 2022/08/17 11:31:16 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__lifestatus(t_philo *philo, int time_to)
{
	if (time_to * 1000 >= (int)philo->hp)
	{
		usleep(philo->hp);
		philo->hp = 0;
		philo->status = DEAD;
		__voice_of_death(philo);
		return (-1);
	}
	else
	{
		philo->hp -= time_to * 1000;
		usleep(time_to);
		return 0;
	}
}

/************************ voice *************************/
int	__waiting_to_speak(t_philo *philo)
{
	while (1)
	{
		if (((t_philo *)philo)->data->the_voice->__data.__lock == 0)
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

int	__voice(t_philo *philo, char *message)
{
	int	ret;

	ret = 0;
	__waiting_to_speak(philo);
	pthread_mutex_lock(philo->data->the_voice);
	if (philo->data->blood_switch == 0)
	{
		printf("%07lld %d %s\n",
		__voice_time(philo->data->start_time, __get_time()), philo->id + 1,
		message);
	}
	else
		ret = -1;
	pthread_mutex_unlock(philo->data->the_voice);
	return (ret);
}

void	__voice_of_death(t_philo *philo)
{
	__waiting_to_speak(philo);
	pthread_mutex_lock(philo->data->the_voice);
	if (philo->data->blood_switch == 0)
	{
		philo->data->blood_switch++;
		philo->status = DEAD;
		printf("%lld %d died\n",
		__voice_time(philo->data->start_time, __get_time()), philo->id + 1);
	}
	pthread_mutex_unlock(philo->data->the_voice);
}
