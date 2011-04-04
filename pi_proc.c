#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
/*
	Thiago Araujo - para BCC-SO.
*/
double monteCarloPi(int n, int seed);

int main (int argc, char* argv){
		printf("Método de Monte Carlo para calculo de pi \n");

		int n = 1000000000;
		printf("n = %d \n", n);
		
		time_t start,end;
		double pi1, pi2;

		int pid = fork();
		if(pid > 0){
			time (&start);
			pi1 = monteCarloPi(1000000, 123456);
			
			printf("estimativa do pai: pi1 = %f \n", pi1);
		}
		if(pid == 0) wait(10);
		if(pid == 0){
			pi2 = monteCarloPi(1000000, time(NULL));			
			time(&end);
			printf("estimativa do filho: pi2 = %f \n", pi2);
		}
		if(pid == 0) wait(NULL);
		
		if(pid > 0){
			double piFim = (pi1 + pi2) * 0.5;
			double dif = difftime (end,start);
			printf("tempo =%6.0f \n", dif);
			printf("pi final = %f \n", piFim);
		}
		exit(EXIT_SUCCESS);
	}

	double monteCarloPi(int n, int seed){
		if (n <= 0){ 
			printf("numero de iteracoes deve ser > 0! \n");
			return 0;
		}

		printf("metodo monte carlo para pi (n = %d)... \n", n);

		double nDentro = 0.0;
		double x = 0.0;
		double y = 0.0;
		srand(seed) ;
		for (int i = 0; i < n; i++){
			x = ((double)rand() / (double)RAND_MAX);
			y = ((double)rand() / (double)RAND_MAX);		
			if( sqrt(x * x + y * y) <= 1) nDentro = nDentro + 1;
		}	

		return 4 * (nDentro / n);
}
