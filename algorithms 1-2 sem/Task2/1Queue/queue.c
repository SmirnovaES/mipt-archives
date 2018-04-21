#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

typedef struct list queue;

queue* queue_new() {
    return list_new();
}

void queue_delete(queue* q) {
    list_delete(q);
}

void add(queue* q, int val) {
    unshift(q, val);
}

void pop(queue* q, int* result) {
    pop_from_list(q, result);
}


