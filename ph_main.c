/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:56:04 by lchan             #+#    #+#             */
/*   Updated: 2022/08/14 16:19:01 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__launch_philo(t_data *data, int nbr)
{
	int	i;

	i = -1;
	if (nbr)
	{
		while (++i < nbr)
			if(pthread_create(&((data->philo_tab[i]).ph_thread), \
			NULL,\
			&__routine, (void *)&data->philo_tab[i]))
				return (i);
	}
	return (0);
}

int	__join_philo(t_data *data, int nbr)
{
	int	i;

	i = -1;
	if (nbr)
		while (++i < nbr)
			pthread_join((data->philo_tab[i].ph_thread), NULL);
	return (0);
}

// void	__wait_for_blood(t_data *data)
// {
// 	t_philo *philo_start;
// 	t_philo	*philo_end;

// 	philo_start = data->philo_tab;
// 	philo_end = data->philo_tab + data->philo_nbr - 1;
// 	while (1)
// 	{
// 		while (philo_start <= philo_end)
// 		{
// 			if (philo_start->status == DEAD)
// 			{
// 				write(1, "DEATH DETECTED\n", 15);
// 				pthread_mutex_lock(data->the_voice);
// 				data->blood++;
// 				pthread_mutex_unlock(data->the_voice);
// 				break ;
// 			}
// 			philo_start++;
// 		}
// 		philo_start = data->philo_tab;
// 		if (data->blood >= 1)
// 			break ;
// 	}
// }

void	__wait_for_blood(t_data *data)
{
	while (1)
		if (data->blood != 0)
			break;

}

int	main (int ac, char **av)
{
	t_data		data;

	if (__init_data(ac -1, av + 1, &data) == -1)
		return (-1);
	if (__set_table(&data) == -1)
		return (-1);
	__visual(&data, DATA);
	__launch_philo(&data, data.philo_nbr);
	//__wait_for_blood(&data);
	__join_philo(&data, data.philo_nbr);
	__ultimate_free(&data);
	printf("end of main process\n");
	return (0);
}

//https://stackoverflow.com/questions/30585375/what-is-the-type-of-pthread-mutex-t
//valgrind --tool=helgrind ./philo 200 200 200 200
