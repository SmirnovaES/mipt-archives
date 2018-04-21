#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int* a, int l, int r) {
    int pivot = a[r];
    int i = l - 1;
    int j = r;
    while(1) {
        while(a[++i] < pivot);
        while(a[--j] > pivot) {
            if (j <= i) break;
        }
            if (j <= i) break;
        swap(&a[i], &a[j]);
    }
    swap(&a[i], &a[r]);
    return i;
}

int find_order_statistic(int* array, int n, int k) {
    int left = 0;
    int right = n - 1;
    while(1) {
        int mid = partition(array, left, right);
        if (mid == k) return array[mid];
        else if (k < mid) right = mid - 1;
        else {
            left = mid + 1;
        }
    }
}

int* get_statistics(int** matrix, int* k_array, int m, int n) {
    int* k_statistics = (int*) malloc(sizeof(int) * m);
    int i;
    for (i = 0; i < m; i++) {
        k_statistics[i] = find_order_statistic(matrix[i], n, k_array[i]);
    }
    return k_statistics;
}

int* generate_array(int n) {
    int* array = (int*) malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % 10;
    }
    return array;
}

int** get_matrix(int m, int n) {
    int** matrix = (int**) malloc(sizeof(int*) * m);
    int i;
    for (i = 0; i < m; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * n);
    }
    for (i = 0; i < m; i++) {
        int j;
        for (j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    return matrix;
}

int* get_array(int n) {
    int* array = (int*) malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    return array;
}

void print_array(int* array, int arrayLength) {
    printf("Now the array looks like:\n");
    int i;
    for (i = 0; i < arrayLength; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void print_matrix(int** matrix, int m, int n) {
    int i;
    for (i = 0; i < m; i++) {
        print_array(matrix[i], n);
        printf("\n");
    }
}

int main() {
    int n, m;
    printf("Enter the matrix's size:\n");
    scanf("%d %d", &m, &n);
    printf("Enter the matrix:\n");
    int** matrix = get_matrix(m, n);
    printf("Enter the B vector:\n");
    int* k_array = get_array(m);
    int* k_statistics = get_statistics(matrix, k_array, m, n);
    print_array(k_statistics, m);
    return 0;
}
