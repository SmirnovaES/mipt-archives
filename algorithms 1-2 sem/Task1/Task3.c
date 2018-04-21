#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mem_rotr(void *p, unsigned size, unsigned k) {
    char* buff = (char*) malloc(size);
    char* uc = (char*) p;
    int i;
    memcpy(buff, uc + size - ((k / 8) % size), (k / 8) % size);
    memcpy(buff + (k / 8) % size, uc, size - (k / 8) % size);
    memcpy(uc, buff, size);
    free(buff);
    char leftPart = uc[size - 1] << (8 - (k % 8));
    for (i = 0; i < size; i++) {
        char t = leftPart | (uc[i] >> (k % 8));
        leftPart = uc[i] << (8 - (k % 8));
        uc[i] = t;
    }
}

//from task5
void printByte(char data) {
    int i;
    for (i = 7; i >= 0; i--) {
        printf("%d", (data & (1 << i)) >> i);
    }
}

void printBitwiseRepresentation (void* data, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printByte(*((char*) data + i));
        printf(" ");
    }
    printf("\n");
}

int main() {
    int n;
    int k;
    printf("Enter the number and size of shift:\n");
    scanf("%d %d", &n, &k);
    printf("Now this number looks like:\n");
    printBitwiseRepresentation(&n, sizeof(int));
    mem_rotr(&n, sizeof(int), k);
    printf("After shift the number looks like:\n");
    printBitwiseRepresentation(&n, sizeof(int));
    return 0;
}
