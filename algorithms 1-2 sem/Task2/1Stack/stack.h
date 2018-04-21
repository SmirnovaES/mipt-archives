#include "list.h"

#ifndef STACK
#define STACK

typedef struct list stack;

stack* stack_new();

void stack_delete(stack* st);

void push(stack* st, int val);

void pop(stack* st, int* x);
#endif
