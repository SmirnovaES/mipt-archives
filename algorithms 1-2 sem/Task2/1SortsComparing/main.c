#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bubble.h"
#include "merge.h"
#include "impquick.h"
#include "shell.h"
#include "quick.h"

int comparing(void* a, void* b) { //return -1 if a < b, return 0 if a == b, return 1 if a > b
    if (*((int*) a) - *((int*) b) < 0) {
        return -1;
    } else if (*((int*) a) - *((int*) b) > 0) {
        return 1;
    } else return 0;
}

int* generateArray(int n) {
    int* array = (int*) malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % 100;
    }
    return array;
}

int main() {
    int n = 10000;
    int* array = generateArray(n);
    clock_t cs_bubble = clock();
    bubbleSort(array, n);
    clock_t cf_bubble = clock();
    double bubble_time = (double) (cf_bubble - cs_bubble) / CLOCKS_PER_SEC;

    array = generateArray(n);
    clock_t cs_merge = clock();
    mergeSort(array, sizeof(int), n, &comparing);
    clock_t cf_merge = clock();
    double merge_time = (double) (cf_merge - cs_merge) / CLOCKS_PER_SEC;

    array = generateArray(n);
    clock_t cs_impquick = clock();
    impQuickSort(array, sizeof(int), 0, n - 1, &comparing);
    clock_t cf_impquick = clock();
    double impquick_time = (double) (cf_impquick - cs_impquick) / CLOCKS_PER_SEC;

    array = generateArray(n);
    clock_t cs_shell = clock();
    ShellSort(array, n);
    clock_t cf_shell = clock();
    double shell_time = (double) (cf_shell - cs_shell) / CLOCKS_PER_SEC;

    array = generateArray(n);
    clock_t cs_quick = clock();
    quickSort(array, sizeof(int), 0, n - 1, &comparing);
    clock_t cf_quick = clock();
    double quick_time = (double) (cf_quick - cs_quick) / CLOCKS_PER_SEC;

    printf("Difference between bubble and quick is %lf sec.\n", bubble_time - quick_time);
    printf("Difference between bubble and merge is %lf sec.\n", bubble_time - merge_time);
    printf("Difference between quick and impquick is %lf sec.\n", quick_time - impquick_time);
    return 0;
}
