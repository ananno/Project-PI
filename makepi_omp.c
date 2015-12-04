#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define VIZ 0
#define MAX_THREAD 8192
#define STEPS 1000000000

int main(int argc, char *argv[]) {
	float r;
	double pi_cal, l;
	const double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
	time_t sTime, eTime;
	long n, blockcount;
	long c[MAX_THREAD], s[MAX_THREAD];
	
	blockcount = (long)(STEPS/MAX_THREAD);

	r = 0.25;

	printf("\n=====|| Starting Simulation ||=====\n");	
	printf("\nStart calculating PI with parallel monte-carlo simulation method...\n");
	printf("\nTotal step : %d, with Threads : %d\n", (blockcount*MAX_THREAD), MAX_THREAD);
	printf("\nInitializing ...\n");	
#pragma omp parallel for schedule(static) shared(c,s) private(n)
	for(n=0; n < MAX_THREAD; n++) {
		c[n] = 0;
		s[n] = 0;
	}
	printf("\nRunning Simulation...\n");
#pragma omp parallel private(n) shared(blockcount, c, s, r)
{
	int thread_id = omp_get_thread_num();
	srand((int)(time(NULL)) ^ thread_id);	
#pragma omp for schedule(static) 
	for(n = thread_id; n < ((thread_id+1) * blockcount); n++){
		float x = (0.5 - ((float)rand()/RAND_MAX));
		float y = (0.5 - ((float)rand()/RAND_MAX));
		
		float l = ((x*x) + (y*y));
		
		c[thread_id] += l <= r ? 1 : 0;
		s[thread_id] += 1;
		
		if (VIZ > 1) {
			printf("T: %d	X: %f	Y: %f	L: %f	C: %d	S: %d	PI: %f \n" ,thread_id, x,y,l,(long)c[thread_id],s[thread_id], ((double)4*c[thread_id]/s[thread_id]));
		}
	}
}
	long cT = 0.0, sT = 0.0;
	printf("\nPreparing results...\n");
#pragma omp parallel for schedule(static) shared(c,s) reduction(+:cT,sT)
	for (n = 0; n < MAX_THREAD; n++) {
		cT += c[n];
		sT += s[n];
		if (VIZ > 0) {
			printf("Thread : %d	cT: %d	sT: %d 	PI: %10f\n",omp_get_thread_num(),cT,sT,(double)(4.0*cT/sT));
		}
	}
	pi_cal = (double)(4.0 * cT / sT);
	printf("\nPI: %10f		Steps: %d		Difference: %8f		Threads: %d\n", pi_cal, STEPS, (pi-pi_cal), MAX_THREAD);
	printf("\n====|| Simulation complete ||=====\n");
}
