/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 20:39:10 by lchan             #+#    #+#             */
/*   Updated: 2022/08/17 10:57:13 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__is_even_nbr(int n)
{
	if (n == 0 || n == -1 || n == 1)
		return (0);
	if (n % 2 == 0 || n == 2)
		return (1);
	return (0);
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
