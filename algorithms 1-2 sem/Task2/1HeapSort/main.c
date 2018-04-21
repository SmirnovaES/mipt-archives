#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heap.h"

int* generateArray(int n) {
    int* array = (int*) malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++)
    {
        array[i] = rand() % 32;
    }
    return array;
}

int* getSortedArray(int* a, int n) {
    heap* h = build_heap(a, n);
    int i;
    for (i = 0; i < n; i++) {
        a[i] = pop(h);
    }
    return a;
}

void printArray(int* array, int arrayLength) {
    int i;
    for (i = 0; i < arrayLength; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int checking(int* a, int n) {
    int i;
    int b = 1;
    for (i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            b = 0;
            break;
        }
    }
    return b;
}

int main() {
    int n = 100;
    int* array = generateArray(n);
    array = getSortedArray(array, n);
    int b = checking(array, n);
    if (b) {
        printf("Success");
    } else {
        printf("Fail");
    }
    free(array);
    return 0;
}
