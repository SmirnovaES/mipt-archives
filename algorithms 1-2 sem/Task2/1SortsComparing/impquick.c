#include <stdio.h>
#include <stdlib.h>
#include "impquick.h"
#include "swap.h"

void insertionSort(void* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b)) {
    int i;
    for (i = l; i <= r; i++) {
        int j;
        for (j = i; j >= l; j--) {
            if ((*comparing) ((void*) ((char*)array + (j + 1) * element_size), (void*) ((char*)array + (j) * element_size)) < 0 && j != r) {
                swap((void*) ((char*) array + (j + 1) * element_size), (void*) ((char*) array + j * element_size), element_size);
            }
        }
    }
}

int partition_imp(int* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b)) {
    int random = l + rand() % (r - l + 1);
    swap((void*) ((char*) array + random * element_size), (void*) ((char*) array + r * element_size), element_size);
    void* pivot = malloc(element_size);
    pivot = (void*) ((char*)array + r * element_size);
    int i = l - 1;
    int j = r;
    while(1) {
        while((*comparing) ((void*) ((char*)array + (++i)*element_size), pivot) < 0);
        while((*comparing) ((void*) ((char*)array + (--j)*element_size), pivot) > 0) {
            if (j <= i) break;
        }
        if (j <= i) break;
        swap((void*) ((char*)array + (i)*element_size), (void*) ((char*)array + (j)*element_size), element_size);
    }
    swap((void*) ((char*)array + (i)*element_size), (void*) ((char*)array + (r)*element_size), element_size);
    free(pivot);
    return i;
}

void impQuickSort(void* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b)) {
    if (r - l <= 10) {
        insertionSort(array, element_size, l, r, comparing);
        return;
    }
    int i = partition_imp(array, element_size, l, r, comparing);
    impQuickSort(array, element_size, l, i - 1, comparing);
    impQuickSort(array, element_size, i + 1, r, comparing);
}
