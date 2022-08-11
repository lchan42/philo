#include "philo.h"


int	test_index = 0;
int	nbr_thread = 5;
pthread_mutex_t m1;

void	*rout(void *i)
{
	pthread_mutex_lock(&m1);
	printf("I am the routine %d\n", test_index);
	printf("ending routine %d\n", test_index);
	test_index++;
	pthread_mutex_unlock(&m1);
}

int	main(void)
{
	int			i = 0;
	int			j = -1;
	pthread_t	thread[nbr_thread];

	pthread_mutex_init(&m1, NULL);
	while (j++ < nbr_thread)
		pthread_create(&thread[j], NULL, &rout, (void *)&i);
	j = 0;
	while (j++ < nbr_thread)
		pthread_join(thread[j], NULL);
	pthread_mutex_destroy(&m1);
	printf("main process is here\n");
	return (0);
}
