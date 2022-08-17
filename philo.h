/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:10:38 by lchan             #+#    #+#             */
/*   Updated: 2022/08/17 22:00:28 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define INT_MAX 2147483647
#define	INIT_SIZE 3
#define	FREE_FUNK 3
#define TT_THINK 1
#define FORK_MESS "has taken a fork"
#define EAT_MESS "is eating"
#define SLEEP_MESS "is sleeping"
#define THINK_MESS "is thinking"
#define DEATH_MESS "died"

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
 * to check into a mutex structure philo.rgt.__data.__lock
 * 		https://stackoverflow.com/questions/30585375/what-is-the-type-of-pthread-mutex-t
 * valgrind --tool=helgrind to check race conditions
************************************/


 /*****
  * timestamp_in_ms X has taken a fork
  * timestamp_in_ms X is eating
  * timestamp_in_ms X is sleeping
  * timestamp_in_ms X is thinking
  * timestamp_in_ms X died
  * philo.rgt.__data.__lock
 ****/



typedef struct s_data{	// neeed to add a time to think
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
	int				status; //useless
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

enum e_status{
	WAITING,
	ALIVE,
	DEAD,
	EAT,
	SLEEP,
	THINK
};

enum e_visual{ //have to delete this enum afterwards
	ALL = -1,
	DATA,
	TABLE_SET,
	PHILO_TAB
};

/******** ********/

/******** visual ********/
void	__visual_print_data(t_data *data, int nbr);
void	__visual(t_data *data, int opt);

/******** main struct init ********/
int			__init_data(int ac, char **av, t_data *data);
int			__set_starting_time(/*t_data *data*/long long *start_time);

/******** table set ********/
int			__set_table(t_data *data);

/******** philo routine ********/
void		*__routine(void *philo_void);

/******** routune ********/
int			__eat(t_philo *philo);
int			__sleep(t_philo *philo);

/******** voice ********/
int		__voice(t_philo *philo, char *message);
int	__add_to_rqrmt(t_philo *philo);
//int	__voice(t_philo *philo, int time_to, char *message);
void		__voice_of_death(t_philo *philo);
int			__lifestatus(t_philo *philo, int time_to);

/******** utils ********/
int			__is_even_nbr(int n);
		//utils for time mgmt
long long	__get_time();
long long	__voice_time(long long start, long long now);
int			__waiting_to_speak(t_philo *philo);

/******** free functions ********/
void		__table_free(t_data *data);
void		__ultimate_free(t_data *data);
void		 __free_setnull(void **malloc_elem); // not sure it is usefull

#endif


// 12/08 objf -> infinit philo loop taking fork
// I m not sure about where to put my thread. in Philo struct or main struct?

// after coffee : make a visual for forks and philosophers (see who is holding who s fork)DONE

//figure out exactly how threads are working;
//try to figure out how to deal with errors from __routine.




// convert every value in long long (creat a val called bigi)


//
/**************************
 * il faut changer check eat rqmt. il doit etre placer dans les mutex;
 * DONE la variable prev_lunch ne sert a rien
 * DONE		la fonction the voice semble pouvoir etre faite avec une seule fonction __voice(t_philo *philo, char *message)
 * il semble que le time of death est incorrect
 * reduire le nombre de fonction
 * ************************/


/************
 * essayer de prendre une fourchette a la fois.(dansle waiting to eat ... )
 * essayer de mettre le get_time directement dans la structure du philosophe.
 * le philo status semble ne servir a rien
 * ****/

