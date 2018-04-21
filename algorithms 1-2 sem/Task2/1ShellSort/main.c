#include <stdio.h>
#include <stdlib.h>

void swap (int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int comparing(int a, int b) {
    if (a < b) return -1;
    if (a == b) return 0;
    if (a > b) return 1;
}

int checking(int* a, int n, int (*comparing) (int, int)) {
    int i;
    int flag = 1;
    for (i = 0; i < n - 1; i++) {
        if ((*comparing) (a[i], a[i + 1]) > 0) {
            flag = 0;
            break;
        }
    }
    return flag;
}

void ShellSort(int* array, int arr_size, int (*comparing)(int, int)) {
	int i, j;
	int step;
	for(step = arr_size / 2; step > 0; step /= 2) {
        for(i = 0; i < step; i++) {
            for(j = i + step; j < arr_size; j += step) {
                int k;
                for (k = j; k > i; k -= step) {
                    if ((*comparing) (array[k], array[k - step]) < 0) {
                        swap(&array[k], &array[k - step]);
                    }
                }
            }
        }
	}
}

int* generateArray(int n) {
    int* array = (int*) malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % 10;
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
    int n;
    printf("Enter the size of an array:\n");
    scanf("%d", &n);
    int* array = generateArray(n);
    printArray(array, n);
    ShellSort(array, n, &comparing);
    printArray(array, n);
    if (checking(array, n, &comparing)) {
        printf("I have sorted this array for you.\n");
    } else {
        printf("My algorithm has not worked right, just trust me.\n");
    }
    free(array);
    return 0;
}
