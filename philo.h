/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:10:38 by lchan             #+#    #+#             */
/*   Updated: 2022/06/23 19:35:23 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define INT_MAX 2147483647


/*************************************
 * autorised functions:
 * void *memset(void *s, int c, size_t n);
 * 						fill s with c on n bytes
 * int usleep(useconds_t usec);
 * 						returns 0 on success.  On error, -1 is  returned, with errno set to indicate the cause of the error.
 * int gettimeofday(struct timeval *tv, struct timezone *tz);
 * 						The tv argument is a struct timeval (as specified in <sys/time.h>):
 * 						struct timeval
 * 						{
 * 							time_t      tv_sec;     // seconds
 * 							suseconds_t tv_usec;    // microseconds
 * 						};
 * 						return 0 for success, or -1 for failure (in which case errno is set appropriately).

 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
************************************/

typedef struct s_data{
	int			philo_nbr;
	int			ttdie;
	int			ttsleep;
	int			tteat;
	int			eat_rqrmt;
	long long	start_time;
	//mutex *tab of fork
}	t_data;

typedef struct s_philo{
	int			id;
	int			status;
	long long	prev_lunch;
	//mutex for right fork
	//mutex for left fork
	t_data	*data;
}	t_philo;

enum e_err_parsing{
	INVALID_NBR_ARG = 1,
	NULL_STR_CASE,
	NOT_DIGIT,
	OVERFLOW,
	TOO_MUCH_PHILO,
	TIME_SET_ERR
};

enum e_status{
	ALIVE,
	DEAD,
	EAT,
	SLEEP
};

//visual
void	__visual_print_data(t_data *data);
int	__init_data(int ac, char **av, t_data *data);
void	routine(void);
#endif
