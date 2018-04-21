#include <stdio.h>
#include <stdlib.h>
#include "bubble.h"

void swap_int(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubbleSort(int* array, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap_int(&array[j], &array[j + 1]);
            }
        }
    }
}
