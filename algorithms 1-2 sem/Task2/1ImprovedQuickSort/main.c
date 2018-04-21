#include <stdio.h>
#include <stdlib.h>

int comparing(void* a, void* b) { //return -1 if a < b, return 0 if a == b, return 1 if a > b
    if (*((int*) a) - *((int*) b) < 0) {
        return -1;
    } else if (*((int*) a) - *((int*) b) > 0) {
        return 1;
    } else return 0;
}

int checking(void* array, size_t element_size, int array_size, int (*comparing)(void* a, void* b)) {
    int i;
    int flag = 1;
    for (i = 0; i < array_size - 1; i++) {
        if ((*comparing) ((void*) ((char*) array + i * element_size), (void*) ((char*) array + (i + 1) * element_size)) > 0) {
            flag = 0;
            break;
        }
    }
    return flag;
}

void swap(void* a, void* b, size_t element_size) {
	void* t = malloc(element_size);
	memcpy(t, a, element_size);
	memcpy(a, b, element_size);
	memcpy(b, t, element_size);
	free(t);
}

void insertionSort(void* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b)) {
    int i;
    for (i = l; i <= r; i++) {
        int j;
        for (j = i; j >= l; j--) {
            if ((*comparing) ((void*) ((char*)array + (j + 1) * element_size), (void*) ((char*)array + (j) * element_size)) < 0 && j != r) {
                swap((void*) ((char*) array + (j + 1) * element_size), (void*) ((char*) array + j * element_size), element_size);
            }
        }
        //printf("%d \n", 5);
    }
}

int partrition(void* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b)) {
    int random = l + rand() % (r - l + 1);
    swap((void*) ((char*) array + random * element_size), (void*) ((char*) array + r * element_size), element_size);
    void* pivot = malloc(element_size);
    pivot = (void*) ((char*)array + r * element_size);
    int i = l - 1;
    int j = r;
    while(1) {
        while((*comparing) ((void*) ((char*)array + (++i)*element_size), pivot) < 0);
        while((*comparing) ((void*) ((char*)array + (--j)*element_size), pivot) > 0) {
            if (j <= i) break;
        }
        if (j <= i) break;
        swap((void*) ((char*)array + (i)*element_size), (void*) ((char*)array + (j)*element_size), element_size);
    }
    swap((void*) ((char*)array + (i)*element_size), (void*) ((char*)array + (r)*element_size), element_size);
    free(pivot);
    return i;
}

void quickSort(void* array, size_t element_size, int l, int r, int (*comparing) (void* a, void* b)) {
    if (r - l <= 10) {
        insertionSort(array, element_size, l, r, comparing);
        return;
    }
    int i = partrition(array, element_size, l, r, comparing);
    quickSort(array, element_size, l, i - 1, comparing);
    quickSort(array, element_size, i + 1, r, comparing);
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
    int i;
    for (i = 0; i < arrayLength; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main()
{
   printf("Enter the size of array\n");
    int n;
    scanf("%d", &n);
    int* array = generateArray(n);
    quickSort(array, sizeof(int), 0, n - 1, &comparing);
    if (checking((void*) array, sizeof(int), n, &comparing)) {
        printf("Sort is successful.\n");
    } else {
        printf("Sort is failed.\n");
    }
    free(array);
    return 0;
}
