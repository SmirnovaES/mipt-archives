#include <stdio.h>
#include <stdlib.h>

//there is only int-generating

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

int comparing(void* a, void* b) { //return -1 if a < b, return 0 if a == b, return 1 if a > b
    if (*((int*) a) - *((int*) b) < 0) {
        return -1;
    } else if (*((int*) a) - *((int*) b) > 0) {
        return 1;
    } else return 0;
}

void swap(void* a, void* b, size_t element_size) {
	void* t = malloc(element_size);
	memcpy(t, a, element_size);
	memcpy(a, b, element_size);
	memcpy(b, t, element_size);
	free(t);
}

void merge(void* array, void* sup, size_t element_size, int m, int l, int r, int (*comparing)(void* a, void* b)) {
    int i = l, j = m + 1, c = l;
		while (i <= m && j <= r) {
			if ((*comparing) ((void*) ((char*) sup + i * element_size), (void*) ((char*) sup + j * element_size)) < 0) {
                memcpy((void*)((char*) array + c * element_size), (void*)((char*) sup + i * element_size), element_size);
				i++;
			} else {
			    memcpy((void*)((char*) array + c * element_size), (void*)((char*) sup + j * element_size), element_size);
				j++;
			}
			c++;
		}
		if (i == m + 1) {
            int f;
			for(f = j; f <= r; f++) {
                memcpy((void*)((char*) array + c * element_size), (void*)((char*) sup + f * element_size), element_size);
				c++;
			}
		} else {
		    int f;
			for(f = i; f <= m; f++) {
                memcpy((void*)((char*) array + c * element_size), (void*)((char*) sup + f * element_size), element_size);
				c++;
			}
		}
}

void mergeSortAB (void* array, void* sup, size_t element_size, int l, int r, int (*comparing)(void* a, void* b)) {
    if (r <= l) return;
    int m = (l + r) / 2;
    mergeSortAB(sup, array, element_size, l, m, comparing);
    mergeSortAB(sup, array, element_size, m + 1, r, comparing);
    merge(array, sup, element_size, m, l, r, comparing);
}

void mergeSort(void* array, size_t element_size, int array_size, int (*comparing)(void* a, void* b)) {
    void* sup = malloc(element_size * array_size);
    memcpy(sup, array, element_size * array_size);
    mergeSortAB(array, sup, element_size, 0, array_size - 1, comparing);
    free(sup);
}

int* generateArray(int n) {
    int* array = (int*) malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % 32;
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

int main() {
    printf("Enter the size of array\n");
    int n;
    scanf("%d", &n);
    int* array = generateArray(n);
    printArray(array, n);
    mergeSort(array, sizeof(int), n, &comparing);
    printArray(array, n);
    if (checking((void*) array, sizeof(int), n, &comparing)) {
        printf("Sort is successful.\n");
    } else {
        printf("Sort is failed.\n");
    }
    free(array);
    return 0;
}
