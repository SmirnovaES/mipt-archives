#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
	FILE* output = fopen("out.txt", "w");
	int a, b, x, N, P;
	float p;
	scanf("%d %d %d %d %f %d", &a, &b, &x, &N, &p, &P);
	int right = 0, left = 0;
	float total_time = 0.0;
	struct timespec t1, t2;
	{
		int i;
		int curr_pos = x;
		int time_ = 0;
		int step = 0;

		clock_gettime(CLOCK_REALTIME, &t1);
		for (i = 0; i < N; i++) {
			while (curr_pos != a && curr_pos != b) {	
				step = rand() % 100;
				time_++;			
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

			total_time += time_;
			curr_pos = x;
			time_ = 0;
		}
		clock_gettime(CLOCK_REALTIME, &t2);
	}
	double work_time = t2.tv_sec - t1.tv_sec + 0.000000001 * (t2.tv_nsec - t1.tv_nsec);
	total_time /= N;
	float answer = (float) right / (float) (right + left);
	fprintf (output, "%.3f %.3f %fs %d %d %d %d %.3f %d\n", answer, total_time, work_time, a, b, x, N, p, P);
	fclose(output);
	return 0;
}
