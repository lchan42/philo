/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_visual.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:13:06 by lchan             #+#    #+#             */
/*   Updated: 2022/08/17 11:01:00 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__visual_print_data(t_data *data, int nbr)
{
	(void) nbr;

	printf(">>>>>>>>>>>> data: <<<<<<<<<<<<\n");
	printf("nbr_philo:		%d\n", data->philo_nbr);
	printf("time_to_die:		%d\n", data->ttdie);
	printf("time_to_eat: 		%d\n", data->tteat);
	printf("time_to_sleep:		%d\n", data->ttsleep);
	printf("eat_requirement:	%d\n", data->eat_rqrmt);
	printf("start+time:		%lld\n", data->start_time);
	printf("table_set:		%p\n", data->table_set);
	printf("the_voice:		%p\n", data->the_voice);
	printf("philo_tab:		%p\n", data->philo_tab);

	printf("\n");
}

void	__visual_print_table_set(t_data *data, int nbr)
{
	int	index = -1;

	if (!data->table_set)
	{
		printf(">>>>>>>>>>>> in table_set : table_set is NULL\n");
		return ;
	}printf(">>>>>>>>>>>> table_set <<<<<<<<<<<<\n");
	while (nbr--)
	{
		++index;
		printf("fork %d address = %p\n", index, data->table_set + index);
	}
	printf("\n");
}

void	__visual_print_philo_tab(t_data *data, int nbr)
{
	int	index = -1;
	t_philo	*philo;

	philo = data->philo_tab;
	if (!philo)
	{
		printf(">>>>>>>>>>>> philo_tab : philo_tab  is NULL\n");
		return ;
	} printf(">>>>>>>>>>>> philo_tab <<<<<<<<<<<<\n");
	while (nbr--)
	{
		++index;
		printf("philo %d right = %p, left = %p\n",
		(philo + index)->id, (philo + index)->rgt, (philo + index)->lft);
	}
	printf("\n");
}

void	__visual(t_data *data, int opt)
{
	int	nbr_funk = 3;
	int	index = -1;
	void ((*__visual_funk[nbr_funk])(t_data *data, int nbr));

	__visual_funk[DATA] = &__visual_print_data;
	__visual_funk[TABLE_SET] = &__visual_print_table_set;
	__visual_funk[PHILO_TAB] = &__visual_print_philo_tab;
	if (opt >= 0)
		__visual_funk[opt](data, data->philo_nbr);
	else
		while (++index < nbr_funk)
			__visual_funk[index](data, data->philo_nbr);
}
