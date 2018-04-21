#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int cmp (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int main(int argc, char **argv) {
    FILE* data = fopen("data.txt", "r");

    int n = atoi(argv[1]);

    int* array = (int*) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        fscanf(data, "%d", &array[i]);
    }
    struct timespec t1, t2;
    clock_gettime(CLOCK_REALTIME, &t1);
    qsort(array, n, sizeof(int), cmp);
    clock_gettime(CLOCK_REALTIME, &t2);

    double work_time = t2.tv_sec - t1.tv_sec + 0.000000001 * (t2.tv_nsec - t1.tv_nsec);

    printf("%lf\n", work_time);

    fclose(data);
    free(array);
}