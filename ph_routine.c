/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:31:08 by lchan             #+#    #+#             */
/*   Updated: 2022/08/17 21:49:10 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__sleep(t_philo *philo)
{
	__voice(philo, SLEEP_MESS);
	return(__lifestatus(philo, philo->data->ttsleep));
}

int	__think(t_philo *philo)
{
	__voice(philo, THINK_MESS);
	return(__lifestatus(philo, philo->ttthink));
}

int	__check_eat_rqmt(t_philo *philo)
{
	return (__add_to_rqrmt(philo));
}

void	*__routine(void *philo)
{

	if (!__is_even_nbr(((t_philo *)philo)->id + 1))
	{
		if (((t_philo *)philo)->id == 0)
			((t_philo *)philo)->data->start_time = __get_time();
		((t_philo *)philo)->hp -= 10;
		usleep(10);
	}
	while (1)
	{
		if (__eat((t_philo *)philo) == -1)
			break ;
		if (__check_eat_rqmt((t_philo *)philo))
			break ;
		if (__sleep((t_philo *)philo) == -1)
			break ;
		if (__think((t_philo *)philo) == -1)
			break ;
		usleep(0);
	}
	return (philo);
}
