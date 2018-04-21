#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void generate_queue(queue* q, int size) {
    int i;
    for (i = 0; i < size; i++) {
        int r = rand() % 100;
        add(q, r);
    }
}

void print_queue(queue* q) {
    int curr_val;
    while(((list*) q)->size != 0) {
        pop(q, &curr_val);
        printf("%d ", curr_val);
    }
    printf("\n");
}

int main() {
    queue* q = queue_new();
    generate_queue(q, 10);
    print_queue(q);
    return 0;
}
