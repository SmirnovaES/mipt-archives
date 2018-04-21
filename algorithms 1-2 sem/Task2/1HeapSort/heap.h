#ifndef HEAP
#define HEAP
typedef struct {
    int* elements;
    int size;
    int capacity;
} heap;

void swap(int* a, int* b);

int min(int a, int b);

void fix_up(heap* h);

void fix_down(heap* h, int i);

heap* build_heap(int* array, int n);

void insert(heap* h, int k);

int top(heap* h);

int pop(heap* h);

#endif // HEAP


