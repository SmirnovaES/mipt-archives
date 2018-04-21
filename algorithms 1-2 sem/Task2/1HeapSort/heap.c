#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void fix_up(heap* h) {
    int i = h->size - 1;
    while (i != 0) {
        if (h->elements[i] < h->elements[(i - 1)/2]) {
            swap(&h->elements[i], &h->elements[(i - 1)/2]);
            i = (i - 1)/2;
        } else break;
    }
}

void fix_down(heap* h, int i) {
    if((2*i + 2 < h->size) && (min(h->elements[2*i + 1], h->elements[2*i + 2]) < h->elements[i])) {
        if (h->elements[2*i + 1] < h->elements[2*i + 2]) {
            swap(&h->elements[2*i + 1], &h->elements[i]);
            i = 2*i + 1;
            fix_down(h, i);
        } else {
            swap(&h->elements[2*i + 2], &h->elements[i]);
            i = 2*i + 2;
            fix_down(h, i);
        }
    } else if ((2*i + 1 < h->size) && h->elements[2*i + 1] < h->elements[i]) {
        swap(&h->elements[2*i + 1], &h->elements[i]);
    }
}

heap* build_heap(int* array, int n) {
    heap* h = (heap*) malloc(sizeof(heap));
    h->size = 0;
    h->capacity = 0;
    h->elements = (int*) malloc(sizeof(int) * h->size);
    int i;
    for (i = 0; i < n; i++) {
        insert(h, array[i]);
    }
    return h;
}

void insert(heap* h, int k) {
    if (h == NULL) {
        int a[1] = {k};
        heap* h = build_heap(a, 1);
    }
    if (++h->size > h->capacity) {
        h->elements = (int*) realloc(h->elements, h->size * 2 * sizeof(int));
        h->capacity = h->size * 2;
    }
    h->elements[h->size - 1] = k;
    fix_up(h);
}

int top(heap* h) {
    return h->elements[0];
}

int pop(heap* h) {
    int t = h->elements[0];
    h->elements[0] = h->elements[h->size - 1];
    h->size--;
    fix_down(h, 0);
    return t;
}
