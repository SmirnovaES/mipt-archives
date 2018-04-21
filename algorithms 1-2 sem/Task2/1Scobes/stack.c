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

void push(stack* st, char val) {
    push_to_list(st, val);
}

void pop(stack* st, char* val) {
    pop_from_list(st, val);
}
