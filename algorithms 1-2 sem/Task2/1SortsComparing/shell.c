#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

void ShellSort(int* array, int arr_size) {
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

