#include <stdio.h>
#include <omp.h>
static long num_pasos = 100000000; 
double paso;

static double limS = 2.0;  //límite superior
static double limI = 1.0;	//límite inferior

#define NUM_THREADS 18


void main() {

	int i, nthreads; 
	double result, sum [NUM_THREADS], t1, t2, tiempo; 
	paso = (limS-limI) / num_pasos; 
	omp_set_num_threads (NUM_THREADS);
	const double startTime = omp_get_wtime();

#pragma omp parallel

{

	int i, id, nthrds; 
	double x;
	id = omp_get_thread_num(); 
	nthrds = omp_get_num_threads(); 
	if (id==0) nthreads=nthrds; 

	for (i=id, sum[id] =0.0;i<num_pasos; i=i+nthrds) {
		x=((i + ((limS-limI)/2)) * paso) + limI;
		sum[id]+=1/x; //función a integrar

	} 
}

for (i=0,result=0.0;i<nthreads; i++) {
	result+=sum[i]*paso;
	
}
	const double endTime = omp_get_wtime();
	tiempo=t2-t1;
	printf("El resultado es = (%lf), usando %ld pasos \n",result,num_pasos); 
	printf("Con un tiempo de ejecución de %lf\n\n", (endTime - startTime));

}
