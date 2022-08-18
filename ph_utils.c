/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 20:39:10 by lchan             #+#    #+#             */
/*   Updated: 2022/08/18 13:58:59 by lchan            ###   ########.fr       */
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

int	__abs_val(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}




size_t	ft_strlen_p(const char *s)
{
	char	*start;

	if (s)
	{
		start = (char *)s;
		while (*s)
			s++;
		return (s - start);
	}
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		write (fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	nb = nb % 10 + '0';
	write (fd, &nb, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write (fd, s, ft_strlen_p(s));
}

void	__print_mess(int start_t, int id, char *mess)
{
	ft_putnbr_fd(start_t, 1);
	write(1, " ", 1);
	ft_putnbr_fd(id, 1);
	write(1, " ", 1);
	ft_putstr_fd(mess, 1);
}
