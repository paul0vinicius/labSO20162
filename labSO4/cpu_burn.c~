#include <math.h>
#include <stdio.h>
#include <sys/time.h>
int main() {
	struct timeval inicio, fim;
	long int tempo = 365829000;
	int tmili;
	
	gettimeofday(&inicio, NULL);
	
	while(tempo-- > 0) {
		pow(1.2, 2.3);
	}
	
	gettimeofday(&fim, NULL);
	
	tmili = (int) (1000 * (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec)/1000);
	
	printf("%d\n", tmili);
	
	return 0;
}
