#include "philo.h"


void	*rout(void *i)
{
	int	j;

	j = *((int*)i);
	printf("I am the routine %d\n", j);
//	*((int*)i) = j;
	sleep(3);
	printf("ending routine %d\n", j);
}

int	main(void)
{
	int		i;
	pthread_t	thread[2];

	i = 0;
	while (i < 2)
		pthread_create(&thread[i++], NULL, &rout, (void *)&i);
	i = 0;
	while (i < 2)
		pthread_join(thread[i++], NULL);
	printf("main process is here\n");
	return (0);
	
}
