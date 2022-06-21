/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:02:17 by lchan             #+#    #+#             */
/*   Updated: 2022/06/21 16:58:03 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long int	ft_atol(const char *str)
{
	int			sign;
	long int	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
	if ((*str == '+' || *str == '-') && str++)
			if (*(str - 1) == '-')
					sign = -sign;
	while (*str >= '0' && *str <= '9')
	{
			result = result * 10 + *str - '0';
			str++;
	}
	return (result * (long int)sign);
}

static int	__entrycheck(char *str)
{
	int			i;

	if (!str)
		return (NULL_STR_CASE);
	i = -1;
	while (*str == '0' && str + 1)
		str++;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (NOT_DIGIT);
	if (i > 11 || ft_atol(str) > INT_MAX)
		return (OVERFLOW);
	return (0);
}

static int	__is_error(int error_code)
{
	const char	*err_msg[] = {
	[0] = "",
	[INVALID_NBR_ARG] = "unvalid nbr of argument",
	[NULL_STR_CASE] = "one of the argument is a null byte",
	[NOT_DIGIT] = "argument must be only digit",
	[OVERFLOW] = "argument is too big (overflow)",
	[TOO_MUCH_PHILO] = "there is too much philosophers",
	[TIME_SET_ERR] = "gettimeofday is not working properly"
	};

	if (error_code == 0)
		return (0);
	else
	{
		printf("%s\n", err_msg[error_code]);
		return (-1);
	}
}

static int __set_starting_time(t_data *data)
{
	struct timeval c_time;

	if (gettimeofday(&c_time, NULL) == -1)
		return (-1);
	else
	{
		data->start_time = (c_time.tv_sec *1000 + c_time.tv_usec / 1000);
		return (0);
	}
}

int	__init_data(int ac, char **av, t_data *data)
{
	int	i;
	int	*struct_address;

	i = -1;
	struct_address = (int*)data;
	if (ac < 4 || ac > 5)
		return (__is_error(INVALID_NBR_ARG));
	while (++i < ac)
	{
		if (__is_error(__entrycheck(av[i])) < 0)
			return (-1);
		*(struct_address + i) = (int)ft_atol(av[i]);
	}
	if (data->philo_nbr > 200)
		return (__is_error(TOO_MUCH_PHILO));
	if (i < 5)
		*(struct_address + i) = (long long) -1;
	if (__set_starting_time(data))
		return (__is_error(TIME_SET_ERR));
	return (0);
}
