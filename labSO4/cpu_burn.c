#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <sched.h>


int main(int policy) {
	struct timeval inicio, fim;
	long int tempo = 375839000;
	int tmili;

	struct sched_param param;
	param.sched_priority = 99;
	
	if (policy == 1)
		sched_setscheduler(getpid(), SCHED_FIFO, & param);
	else if (policy == 2)
		sched_setscheduler(getpid(), SCHED_RR, & param);
	
	gettimeofday(&inicio, NULL);
	
	while(tempo-- > 0) {
		pow(1.2, 2.3);
	}
	
	gettimeofday(&fim, NULL);
	
	tmili = (int) (1000 * (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec)/1000);
	
	printf("%d\n", tmili);
	
	return 0;
}
