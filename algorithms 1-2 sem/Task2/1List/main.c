#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void makeListWithPush(list* l, int size) {
    int i;
    for (i = 0; i < size; i++) {
        int curr_val = rand() % 10;
        push(l, curr_val);
    }
}

void makeListWithUnshift(list* l, int size) {
    int i;
    for (i = 0; i < size; i++) {
        int curr_val = rand() % 10;
        unshift(l, curr_val);
    }
}

void printList(list* l) {
    printf("Now the list looks like:\n");
    int i;
    for (i = 0; i < l->size; i++) {
        int x;
        shift(l, &x);
        printf("%d ", x);
        push(l, x);
    }
    printf("\n");
}

int main()
{
    list* l = list_new();
    printf("Enter a size of a list:\n");
    int size;
    scanf("%d", &size);
    makeListWithPush(l, size);
    printList(l);
    printf("Let's reverse the list! ");
    reverse(l);
    printList(l);
    return 0;
}
