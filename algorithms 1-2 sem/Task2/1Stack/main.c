#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"

void generate_stack(stack* st, int size) {
    int i;
    for (i = 0; i < size; i++) {
        int r = rand() % 100;
        push(st, r);
    }
}

void print_stack(stack* st) {
    int curr_val;
    while(((list*) st)->size != 0) {
        pop(st, &curr_val);
        printf("%d ", curr_val);
    }
    printf("\n");
}

int main() {
    stack* st = stack_new();
    generate_stack(st, 10);
    print_stack(st);
    return 0;
}
