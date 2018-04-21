#include "list.h"

#ifndef STACK
#define STACK

typedef struct list stack;

stack* stack_new();

void stack_delete(stack* st);

void push(stack* st, char val);

void pop(stack* st, char* x);
#endif
