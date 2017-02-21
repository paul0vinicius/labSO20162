#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

int main(int sched) {
	struct timeval inicio, fim;
	long int tempo = 375839000;
	int tmili;

	struct sched_param param;
	param.sched_priority = 99;

	if (sched == 1)
		sched_setscheduler(0, SCHED_FIFO, &param);
	else if (sched == 2)
		sched_setscheduler(0, SCHED_RR, &param);
	else
		sched_setscheduler(0, SCHED_OTHER, &param);
	
	gettimeofday(&inicio, NULL);
	
	while(tempo-- > 0) {
		pow(1.2, 2.3);
	}
	
	gettimeofday(&fim, NULL);
	
	tmili = (int) (1000 * (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec)/1000);
	
	printf("%d\n", tmili);
	
	return 0;
}
