/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:31:08 by lchan             #+#    #+#             */
/*   Updated: 2022/08/17 19:30:13 by lchan            ###   ########.fr       */
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

// int	__check_eat_rqmt(t_philo *philo)
// {
// 	if (philo->obj_meal >= 0 && philo->nbr_meal == philo->obj_meal)
// 	return (0);
// }

void	*__routine(void *philo)
{
	if (!__is_even_nbr(((t_philo *)philo)->id + 1))
	{
		((t_philo *)philo)->hp -= 10;
		usleep(10);
	}
	while (1)
	{
		if (__eat((t_philo *)philo) == -1)
			break ;
		//__check_eat_rqmt((t_philo *)philo);
		if (__sleep((t_philo *)philo) == -1)
			break ;
		if (__think((t_philo *)philo) == -1)
			break ;
		//usleep(0);
	}
	return (philo);
}
