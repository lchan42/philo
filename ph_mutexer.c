/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:54:34 by lchan             #+#    #+#             */
/*   Updated: 2022/08/18 11:33:23 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__lifestatus(t_philo *philo, int time_to)
{
	int	time_to_ms;

	time_to_ms = time_to * 1000;
	if (time_to_ms >= philo->hp)
	{
		usleep(philo->hp);
		philo->hp = 0;
		philo->status = DEAD;
		//printf ("philo ->%d has been sentence to die by lifestatus\n", philo->id);
		__voice_of_death(philo);
		return (-1);
	}
	else
	{
		philo->hp -= time_to_ms;
		usleep(time_to_ms);
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
			philo->hp -= 1;
			if (philo->hp <= 0)
			{
				__voice_of_death(philo);
				return (-1) ;
			}
			usleep(1);
		}
	}
}

int	__voice(t_philo *philo, char *message)
{
	int	ret;

	ret = 0;
	__waiting_to_speak(philo);
	pthread_mutex_lock(philo->data->the_voice);
	if (philo->data->blood_switch == 0) /*&& philo->data->rqrmt_switch != philo->data->eat_rqrmt)*/
	{
		printf("%03lld %d %s\n",
		__voice_time(philo->data->start_time, __get_time()), philo->id + 1,
		message);
	}
	else
		ret = -1;
	//printf("voice mutex unlocked by (philo->%d\n)", philo->id + 1);
	pthread_mutex_unlock(philo->data->the_voice);

	return (ret);
}

void	__voice_of_death(t_philo *philo)
{
	pthread_mutex_lock(philo->data->the_voice);
	if (philo->data->blood_switch == 0)
	{
		philo->data->blood_switch++;
		philo->status = DEAD;
		printf("%03lld %d died\n",
		__voice_time(philo->data->start_time, __get_time()), philo->id + 1);
	}
	//printf("death mutex unlocked by (philo->%d\n)", philo->id + 1);
	pthread_mutex_unlock(philo->data->the_voice);
}

int	__add_to_rqrmt(t_philo *philo)
{
	int	ret;

	ret = 0;
	__waiting_to_speak(philo);
	pthread_mutex_lock(philo->data->the_voice);
	//printf("eat rqrmt = %d\n", philo->data->rqrmt_switch);
	if (philo->obj_meal >= 0 && philo->nbr_meal == philo->obj_meal)
		philo->data->rqrmt_switch++;
	if (philo->data->rqrmt_switch >= philo->data->philo_nbr)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(philo->data->the_voice);
	return (ret);
}
