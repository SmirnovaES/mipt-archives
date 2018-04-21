#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int checking(int* a, int n) {
    int i;
    int b = 1;
    for (i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            b = 0;
            break;
        }
    }
    return b;
}

int get_numeral(int n, int rank) {
    return (n % (int) (pow(10, rank + 1))) / pow(10, rank);
}

void sort_one_rank(int* numbers, int rank, int l, int r) {
    int count[10];
    assert(count != NULL);
    int i;
    for (i = 0; i < 10; i++) {
        count[i] = 0;
    }
    for (i = l; i < r; i++) {
        count[get_numeral(numbers[i], rank) + 1]++;
    }
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    int count_copy[10];
    memcpy(count_copy, count, sizeof(int) * 10);
    int* support = (int*) malloc(sizeof(int) * (r - l));
    for (i = l; i < r; i++) {
        support[count[get_numeral(numbers[i], rank)]++] = numbers[i];
    }
    for (i = l; i < r; i++) {
         numbers[i] = support[i - l];
    }
    free(support);
    if (rank != 0) {
        for (i = 0; i < 10; i++) {
            if ( i != 9 && count_copy[i] != count_copy[i + 1]) sort_one_rank(numbers, rank - 1, count_copy[i] + l, count_copy[i + 1] + l);
            if ( i == 9 && count_copy[i] != r - l) sort_one_rank(numbers, rank - 1, count_copy[i] + l, r);
        }
    }
}

void RadixSort(int* array, int n) {
    sort_one_rank(array, 9, 0, n);
}

int* generateArray(int n) {
    int* array = (int*) malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % 1000000;
    }
    return array;
}

void printArray(int* array, int arrayLength) {
    printf("Now the array looks like:\n");
    int i;
    for (i = 0; i < arrayLength; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    srand(643);
    int n;
    printf("Enter the size of an array:\n");
    scanf("%d", &n);
    int* array = generateArray(n);
    if (n < 230) {
        printArray(array, n);
    } else printf("I won't print you such a big array.\n");
    RadixSort(array, n);
    if (n < 230 && checking(array, n)) {
        printf("I have sorted this array for you. ");
        printArray(array, n);
    } else if (checking(array, n)) {
        printf("I have sorted this array for you, but it's too big to look on it, just trust me.\n");
    } else if (n < 230) {
        printf("My algorithm has not worked right, but you can still look at the result. ");
        printArray(array, n);
    } else {
        printf("My algorithm has not worked right, just trust me.\n");
    }
    free(array);
    return 0;
}
