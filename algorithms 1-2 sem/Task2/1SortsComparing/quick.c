#include <stdio.h>
#include <stdlib.h>
#include "quick.h"
#include "swap.h"

int partrition(int* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b)) {
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

void quickSort(void* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b)) {
    if (r <= l) return;
    int i = partrition(array, element_size, l, r, comparing);
    quickSort(array, element_size, l, i - 1, comparing);
    quickSort(array, element_size, i + 1, r, comparing);
}
