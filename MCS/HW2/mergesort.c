#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>



int cmp (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}


void generate_array(int* array, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
}

int binSearch(int* array, int left, int right, int x) {
    if (left == right - 1) {
        if (array[left] < x) {
            return left + 1;
        } else {
            return left;
        }
    }

    int mid = (right + left) /2;

    if (array[mid] == x)  {
        return mid;
    } else if (array[mid] > x) {
        return binSearch(array, left, mid, x);
    } else if (array[mid] < x){
        return binSearch(array, mid, right, x);
    }

}

void merge(int* array, int* second_array, int left1, int right1, int left2, int right2, int dest) {
    int curr1 = left1;
    int curr2 = left2;
    while (curr1 < right1 && curr2 < right2) {
        if (array[curr1] < array[curr2]) {
            second_array[dest] = array[curr1];
            curr1++;
        } else {
            second_array[dest] = array[curr2];
            curr2++;
        }
        dest++;
    }
    while (curr1 < right1) {
        second_array[dest] = array[curr1];
        curr1++;
        dest++;
    }
    while (curr2 < right2) {
        second_array[dest] = array[curr2];
        curr2++;
        dest++;
    }
}

void merge_sort(int* array, int* second_array, int left, int right, int m) {
    if (right - left < m) {
        qsort(&array[left], right - left, sizeof(int), cmp);
        return;
    }

    int mid = (right + left) / 2;

    {
        {
            {
                merge_sort(array, second_array, left, mid, m);
            }
            {
                merge_sort(array, second_array, mid, right, m);
            }
        }
    }

    int left_mid = (left + mid) / 2;
    int right_mid = binSearch(array, mid, right, array[left_mid]);

    second_array[left_mid + right_mid - mid] = array[left_mid];

    {
        {
            {
                merge(array, second_array, left, left_mid, mid, right_mid, left);
            }
            {
                merge(array, second_array, left_mid + 1, mid, right_mid, right, left_mid + right_mid - mid + 1);
            }
        }
    }
    memcpy(&array[left], &second_array[left], sizeof(int) * (right - left));
}

int main(int argc, char **argv) {
    FILE* stats = fopen("stats.txt", "w");
    FILE* data = fopen("data.txt", "w");

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int P = atoi(argv[3]);



    int* array = (int*) malloc(sizeof(int) * n);
    generate_array(array, n);

    for (int i = 0; i < n; i++) {
        fprintf(data, "%d ", array[i]);
    }
    fprintf(data, "\n");

    int* second_array = (int*) malloc(sizeof(int) * n);
    memcpy(second_array, array, n * sizeof(int));

    struct timespec t1, t2;
    clock_gettime(CLOCK_REALTIME, &t1);
    merge_sort(array, second_array, 0, n, m);
    clock_gettime(CLOCK_REALTIME, &t2);

    double work_time = t2.tv_sec - t1.tv_sec + 0.000000001 * (t2.tv_nsec - t1.tv_nsec);

    fprintf(stats, "%lf %d %d %d\n", work_time, n, m, P);
    printf("%lf \n", work_time);
    for (int i = 0; i < n; i++) {
        fprintf(data, "%d ", array[i]);
    }
    fprintf(data, "\n");

    fclose(stats);
    fclose(data);
    free(array);
    free(second_array);
}
