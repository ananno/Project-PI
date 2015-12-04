#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define VIZ 1
#define STEPS 1000000000

int main(int argc, char *argv[]) {
	float r;
	double pi_cal, l;
	const double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
	time_t sTime, eTime;
	long n;
	long c, s;

	r = 0.25;

	printf("\n=====|| Starting Simulation ||=====\n");	
	printf("\nStart calculating PI with serial monte-carlo simulation method...\n");
	printf("\nTotal step : %d\n", STEPS);
	printf("\nInitializing ...\n");	
	printf("\nRunning Simulation...\n");
	srand(time(NULL));	
	for(n = 0; n < STEPS; n++){
		float x = (0.5 - ((float)rand()/RAND_MAX));
		float y = (0.5 - ((float)rand()/RAND_MAX));
		
		float l = ((x*x) + (y*y));
		
		c += l <= r ? 1 : 0;
		s += 1;
		
		if (VIZ > 1) {
			printf("X: %f	Y: %f	L: %f	C: %d	S: %d	PI: %f \n", x,y,l,(long)c,(long)s, ((double)(4.0*c/s)));
		}
	}
	printf("\nPreparing results...\n");
	pi_cal = (double)(4.0 * c / s);
	printf("\nPI: %10f		Steps: %d		Difference: %8f	\n", pi_cal, STEPS, (pi-pi_cal));
	printf("\n====|| Simulation complete ||=====\n");
}
