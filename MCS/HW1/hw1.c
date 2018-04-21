#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	FILE* output = fopen("out.txt", "w");
	int a, b, x, N, P;
	float p;
	scanf("%d %d %d %d %f %d", &a, &b, &x, &N, &p, &P);
	int right = 0, left = 0;
	float total_time = 0.0;
	float t1, t2;
	omp_set_num_threads(P);
	#pragma omp parallel shared(left, right, total_time) 
	{
		int i;
		int curr_pos = x;
		int time = 0;
		int step = 0;

		int seed = omp_get_thread_num();
		t1 = omp_get_wtime();
		#pragma omp for	
		for (i = 0; i < N; i++) {
			while (curr_pos != a && curr_pos != b) {	
				step = rand_r(&seed) % 100;
				time++;			
				if (step >= p * 100) {				
					curr_pos++;
				} else {
					curr_pos--;
				}
			}

			if (curr_pos == a) {
				left++;
			} else {
				right++;
			}

			total_time += time;
			curr_pos = x;
			time = 0;
		}
		t2 = omp_get_wtime();
	}
	float work_time = t2 - t1;
	total_time /= N;
	float answer = (float) right / (float) (right + left);
	fprintf (output, "%.3f %.3f %fs %d %d %d %d %.3f %d\n", answer, total_time, work_time, a, b, x, N, p, P);
	fclose(output);
	return 0;
}
