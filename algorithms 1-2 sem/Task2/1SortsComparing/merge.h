#ifndef MERGE
#define MERGE

void merge(void* array, void* sup, size_t element_size, int m, int l, int r, int (*comparing)(void* a, void* b));

void mergeSortAB (void* array, void* sup, size_t element_size, int l, int r, int (*comparing)(void* a, void* b));

void mergeSort(void* array, size_t element_size, int array_size, int (*comparing)(void* a, void* b));

#endif // MERGE


