/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:10:38 by lchan             #+#    #+#             */
/*   Updated: 2022/08/18 18:35:28 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define INT_MAX 2147483647
# define INIT_SIZE 3
# define FREE_FUNK 3
# define TT_THINK 1
# define HP_LOSS 500
# define FORK_MESS "has taken a fork\n"
# define EAT_MESS "is eating\n"
# define SLEEP_MESS "is sleeping\n"
# define THINK_MESS "is thinking\n"
# define DEATH_MESS "died\n"

typedef struct s_data{
	int				philo_nbr;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				eat_rqrmt;
	int				blood_switch;
	int				rqrmt_switch;
	long long		start_time;
	pthread_mutex_t	*table_set;
	pthread_mutex_t	*the_voice;
	struct s_philo	*philo_tab;
}	t_data;

typedef struct s_philo{
	int				id;
	long long		hp;
	int				ttthink;
	int				nbr_meal;
	int				obj_meal;
	pthread_t		ph_thread;
	pthread_mutex_t	*rgt;
	pthread_mutex_t	*lft;
	t_data			*data;
}	t_philo;

enum e_err_parsing{
	INVALID_NBR_ARG = 1,
	NULL_STR_CASE,
	NOT_DIGIT,
	OVERFLOW,
	TOO_MUCH_PHILO,
	TIME_SET_ERR
};

/******** ph_init_data ********/
int			__init_data(int ac, char **av, t_data *data);

/******** ph_set_table ********/
int			__set_table(t_data *data);

/******** ph_routine ********/
void		*__routine(void *philo_void);

/******** ph_eat ********/
int			__eat(t_philo *philo);

/******** ph_mutexer ********/
int			__lifestatus(t_philo *philo, long long int time_to);
int			__voice(t_philo *philo, char *message);
void		__voice_of_death(t_philo *philo);
int			__add_to_rqrmt(t_philo *philo);

/******** ph_utils ********/
int			__is_even_nbr(int n);
int			__abs_val(int n);
long long	__get_time(void);
long long	__voice_time(long long start, long long now);

/******** ph_print_mess ********/
void		__print_mess(int start_t, int id, char *mess);

/******** ph_free ********/
void		__table_free(t_data *data);
void		__ultimate_free(t_data *data);
void		__free_setnull(void **malloc_elem); // not sure it is usefull

/******** visual ********/
enum e_visual{ //have to delete this enum afterwards
	ALL = -1,
	DATA,
	TABLE_SET,
	PHILO_TAB
};
void		__visual_print_data(t_data *data, int nbr);
void		__visual(t_data *data, int opt);

#endif
/*************************************
 * autorised functions:
 * void *memset(void *s, int c, size_t n);
 * 						fill s with c on n bytes
 * int usleep(useconds_t usec);
 * 		returns 0 on success.  On error, -1 is  returned, with errno set to indicate the cause of the error.
 * int gettimeofday(struct timeval *tv, struct timezone *tz);
 * 						The tv argument is a struct timeval (as specified in <sys/time.h>):
 * 						struct timeval
 * 						{
 * 							time_t      tv_sec;     // seconds
 * 							suseconds_t tv_usec;    // microseconds
 * 						};
 * 						return 0 for success, or -1 for failure (in which case errno is set appropriately).

 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
 * to check into a mutex structure philo.rgt.__data.__lock
 * 		https://stackoverflow.com/questions/30585375/what-is-the-type-of-pthread-mutex-t
 * valgrind --tool=helgrind to check race conditions
************************************/
