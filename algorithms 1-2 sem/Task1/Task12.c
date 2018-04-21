#include <stdio.h>
#include <stdlib.h>

int chekingSort(int* sortedArray, int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (sortedArray[i] > sortedArray[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int* bubbleSort(int* array, int n) {
    int* sortedArray = (int*) malloc(sizeof(int)*n);
    memcpy(sortedArray, array, sizeof(int)*n);
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (sortedArray[j] > sortedArray[j + 1]) {
                swap(&sortedArray[j], &sortedArray[j + 1]);
            }
        }
    }
    return sortedArray;
}

int* generateArray(int n) {
    int* array = (int*) malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % 10;
    }
    return array;
}

int* getArrayFromUser(int n) {
    int* array = (int*) malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    return array;
}

int* getArrayFromFile(FILE* file) {
    int n;
    fscanf(file, "%d", &n);
    int* array = (int*) malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++) {
        fscanf(file, "%d", &array[i]);
    }
    return array;
}

void printArray(int* array, int arrayLength) {
    int i;
    for (i = 0; i < arrayLength; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printArrayToFile(FILE* file, int* array, int n) {
    int i;
    for (i = 0; i < n; i++) {
        fprintf(file, "%d ", array[i]);
    }
    fclose(file);
}


int main() {
    srand(342);
    int n = 10;
    int* array = generateArray(n);
    int* sortedArray = bubbleSort(array, n);
    if(chekingSort(sortedArray, n)) {
        printf("Success \n");
    } else {
        printf("Fail \n");
    }
    printArray(sortedArray, n);
    free(array);
    free(sortedArray);
    return 0;
}
