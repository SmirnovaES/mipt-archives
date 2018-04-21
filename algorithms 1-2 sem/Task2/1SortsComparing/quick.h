#ifndef QUICK
#define QUICK

int partrition(int* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b));

void quickSort(void* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b));

#endif // QUICK
