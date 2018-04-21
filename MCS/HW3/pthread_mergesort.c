#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <pthread.h>
#include <omp.h>

typedef struct args_ms {
    int* array;
    int* second_array;
    int left;
    int right;
    int m;
    int available_threads;
    pthread_t* threads;
} args_ms;

typedef struct args_m {
    int* array;
    int* second_array;
    int left1;
    int right1;
    int left2;
    int right2;
    int dest;
    int available_threads;
    pthread_t* threads;
} args_m;

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

void* parallel_merge(void* args) {
    args_m* curr_args = (args_m*) args;
    merge(curr_args->array, curr_args->second_array, curr_args->left1,
          curr_args->right1, curr_args->left2, curr_args->right2, curr_args->dest);
    return NULL;
}

void parallel_merge_(void* args) {
    args_ms* curr_args = (args_ms*) args;
    int mid = (curr_args->right + curr_args->left) / 2;
    int left_mid = (curr_args->left + mid) / 2;
    int right_mid = binSearch(curr_args->array, mid, curr_args->right, curr_args->array[left_mid]);

    args_m args_m_left = {.array = curr_args->array, .second_array = curr_args->second_array,
            .left1 = curr_args->left, .right1 = left_mid, .left2 = mid, .right2 = right_mid, .dest = curr_args->left};

    args_m args_m_right = {.array = curr_args->array, .second_array = curr_args->second_array, .left1 = left_mid + 1,
            .right1 = mid, .left2 = right_mid, .right2 = curr_args->right, .dest = left_mid + right_mid - mid + 1};

    curr_args->second_array[left_mid + right_mid - mid] = curr_args->array[left_mid];

    if (curr_args->available_threads <= 1) {
        parallel_merge(&args_m_left);
        parallel_merge(&args_m_right);
        return;
    }

    pthread_t left_merge = *(curr_args->threads + curr_args->available_threads - 1);
    pthread_t right_merge = *(curr_args->threads + curr_args->available_threads - 2);

    pthread_create(&left_merge, NULL, parallel_merge, &args_m_left);
    pthread_create(&right_merge, NULL, parallel_merge, &args_m_right);

    pthread_join(left_merge, NULL);
    pthread_join(right_merge, NULL);

    memcpy(&curr_args->array[curr_args->left],
           &curr_args->second_array[curr_args->left], sizeof(int) * (curr_args->right - curr_args->left));
    return;
}

void merge_sort(int* array, int* second_array, int left, int right, int m) {
    if (right - left <= m) {
        qsort(&array[left], right - left, sizeof(int), cmp);
        return;
    }

    int mid = (right + left) / 2;

    merge_sort(array, second_array, left, mid, m);
    merge_sort(array, second_array, mid, right, m);

    int left_mid = (left + mid) / 2;
    int right_mid = binSearch(array, mid, right, array[left_mid]);

    second_array[left_mid + right_mid - mid] = array[left_mid];

    merge(array, second_array, left, left_mid, mid, right_mid, left);
    merge(array, second_array, left_mid + 1, mid, right_mid, right, left_mid + right_mid - mid + 1);

    memcpy(&array[left], &second_array[left], sizeof(int) * (right - left));
}


void* parallel_merge_sort(void* args) {
    args_ms* curr_args = (args_ms*) args;
    if (curr_args->available_threads <= 1) {
        merge_sort(curr_args->array, curr_args->second_array, curr_args->left, curr_args->right, curr_args->m);
        return NULL;
    }

    int mid = (curr_args->right + curr_args->left) / 2;
    pthread_t thread_left = *(curr_args->threads + curr_args->available_threads - 1);
    pthread_t thread_right = *(curr_args->threads + curr_args->available_threads - 2);

    args_ms args_left = {.array = curr_args->array, .second_array = curr_args->second_array,
            .left = curr_args->left, .right = mid, .m = curr_args->m,
            .available_threads = (curr_args->available_threads - 2) / 2, .threads = curr_args->threads};

    args_ms args_right = {.array = curr_args->array, .second_array = curr_args->second_array,
            .left = mid, .right = curr_args->right, .m = curr_args->m,
            .available_threads = curr_args->available_threads - 2 - args_left.available_threads, .threads = curr_args->threads};

    pthread_create(&thread_left, NULL, parallel_merge_sort, &args_left);
    pthread_create(&thread_right, NULL, parallel_merge_sort, &args_right);

    pthread_join(thread_left, NULL);
    pthread_join(thread_right, NULL);

    parallel_merge_(curr_args);

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

    pthread_t threads[P];
    args_ms main_args = {.array = array, .second_array = second_array, .left = 0, .right = n,
            .m = m, .available_threads = P, .threads = threads};

    double t1, t2;
    t1 = omp_get_wtime();
    parallel_merge_sort(&main_args);
    t2 = omp_get_wtime();

    fprintf(stats, "%lf %d %d %d\n", t2 - t1, n, m, P);
    for (int i = 0; i < n; i++) {
        fprintf(data, "%d ", array[i]);
    }
    fprintf(data, "\n");

    for (int i = 0; i < n; i++) {
        fprintf(data, "%d ", second_array[i]);
    }
    fprintf(data, "\n");

    fclose(stats);
    fclose(data);
    free(array);
    free(second_array);
}
