#include <stdio.h>
#include <stdlib.h>
#include "merge.h"
#include "swap.h"

void merge(void* array, void* sup, size_t element_size, int m, int l, int r, int (*comparing)(void* a, void* b)) {
    int i = l, j = m + 1, c = l;
		while (i <= m && j <= r) {
			if ((*comparing) ((void*) ((char*) sup + i * element_size), (void*) ((char*) sup + j * element_size)) < 0) {
                memcpy((void*)((char*) array + c * element_size), (void*)((char*) sup + i * element_size), element_size);
				i++;
			} else {
			    memcpy((void*)((char*) array + c * element_size), (void*)((char*) sup + j * element_size), element_size);
				j++;
			}
			c++;
		}
		if (i == m + 1) {
            int f;
			for(f = j; f <= r; f++) {
                memcpy((void*)((char*) array + c * element_size), (void*)((char*) sup + f * element_size), element_size);
				c++;
			}
		} else {
		    int f;
			for(f = i; f <= m; f++) {
                memcpy((void*)((char*) array + c * element_size), (void*)((char*) sup + f * element_size), element_size);
				c++;
			}
		}
}

void mergeSortAB (void* array, void* sup, size_t element_size, int l, int r, int (*comparing)(void* a, void* b)) {
    if (r <= l) return;
    int m = (l + r) / 2;
    mergeSortAB(sup, array, element_size, l, m, comparing);
    mergeSortAB(sup, array, element_size, m + 1, r, comparing);
    merge(array, sup, element_size, m, l, r, comparing);
}

void mergeSort(void* array, size_t element_size, int array_size, int (*comparing)(void* a, void* b)) {
    void* sup = malloc(element_size * array_size);
    memcpy(sup, array, element_size * array_size);
    mergeSortAB(array, sup, element_size, 0, array_size - 1, comparing);
    free(sup);
}
