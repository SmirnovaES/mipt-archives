#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int if_sequence_is_true(stack* st) {
    char curr = getchar();
    int flag = 1;
    int balance = 0;
    while (curr != '0') {
        if (curr == '(' || curr == '{') {
            push(st, curr);
            balance++;
        } else if (curr == '}') {
            if (--balance < 0) break;
            char top;
            pop(st, &top);
            if (top == '(') {
                flag = 0;
                break;
            }
        } else if (curr == ')') {
            if (--balance < 0) break;
            char top;
            pop(st, &top);
            if (top == '{') {
                flag = 0;
                break;
            }
        }
        curr = getchar();
    }
    if (flag == 0 || balance != 0) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    printf("Enter scobes, enter 0 if you have finished.\n");
    stack* st = stack_new();
    if(if_sequence_is_true(st)) {
        printf("Everything is good.\n");
    } else {
        printf("Something is wrong.\n");
    }
    return 0;
}
