#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char **argv) {
	FILE* output = fopen("stats.txt", "w");
	
	int a, b, x, N, P;
	double p;
	int right = 0;
	int total_time = 0;
	double t1, t2;
	
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	x = atoi(argv[3]);
	N = atoi(argv[4]);
	p = atof(argv[5]);
	P = atoi(argv[6]);
	
	omp_set_num_threads(P);
	
	int i;
	srand(time(NULL));
	int* seeds = (int*) malloc(sizeof(int)*P);
	for (i = 0; i < P; i++) {
		seeds[i] = rand();
	}
	
	int curr_pos;
	int* curr_seed;
	double step;
	t1 = omp_get_wtime();
	#pragma omp parallel for private(i, curr_pos, curr_seed, step) shared(seeds) reduction(+: right, total_time)	
	for (i = 0; i < N; i++) {
		curr_pos = x;
		curr_seed = &seeds[omp_get_thread_num()];
		while (curr_pos != a && curr_pos != b) {	
			step = (double) rand_r(curr_seed) / RAND_MAX;
			total_time++;			
			if (step < p) {				
				curr_pos++;
			} else {
				curr_pos--;
			}
		}
		if (curr_pos == b) {
			right++;
		}
	}
	t2 = omp_get_wtime();
	double work_time = t2 - t1;
	double answer = (double) right / N;
	fprintf (output, "%.3f %.3f %lfs %d %d %d %d %.3f %d\n", answer, (float) total_time / N, work_time, a, b, x, N, p, P);
	free(seeds);
	fclose(output);
	return 0;
}
