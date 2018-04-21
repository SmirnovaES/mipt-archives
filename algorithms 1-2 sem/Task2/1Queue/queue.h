#include "list.h"

#ifndef QUEUE
#define QUEUE

typedef struct list queue;

queue* queue_new();

void queue_delete(queue* q);

void add(queue* q, int val);

void pop(queue* q, int* result);

#endif // QUEUE
