#ifndef IMPQUICK
#define IMPQUICK

void insertionSort(void* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b));

int partition_imp(int* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b));

void impQuickSort(void* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b));
#endif // IMPQUICK
