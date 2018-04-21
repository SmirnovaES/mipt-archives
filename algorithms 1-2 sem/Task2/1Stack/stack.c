#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "stack.h"

stack* stack_new() {
    return list_new();
}

void stack_delete(stack* st) {
    list_delete(st);
}

void push(stack* st, int val) {
    push_to_list(st, val);
}

void pop(stack* st, int* val) {
    pop_from_list(st, val);
}
