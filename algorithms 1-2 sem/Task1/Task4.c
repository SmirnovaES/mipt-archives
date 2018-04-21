#include <stdio.h>
#include <stdlib.h>

int** getCantorMatrix(int n) {
    int** array = (int**) malloc(sizeof(int*)*n);
    int i;
    for (i = 0; i < n; i++) {
        array[i] = (int*) malloc(sizeof(int)*n);
    }
    array[0][0] = 1;
    for (i = 1; i < n; i++) {
        array[i][i] = array[i - 1][i - 1] + 2*i;
    }
    for (i = 1; i < n; i++) {
        int j;
        int k1 = array[i][i];
        int k2 = array[i][i];
        for (j = 1; j <= i; j++) {
            if (i % 2 != 0) {
                k1--;
                k2++;
            } else {
                k1++;
                k2--;
            }
            array[i - j][i] = k1;
            array[i][i - j] = k2;
        }
    }
    return array;
}

void printAnswer(int** array, int n) {
    printf("The Cantor matrix looks like:\n");
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d ", array[i][j]);
        }
        printf("\n");
    }
}

void fullFree(int** array, int n) {
    int i;
    for (i = 0; i < n; i++) {
        free(array[i]);
    }
    free(array);
}

int main()
{
    int n;
    printf("Enter the size of matrix:\n");
    scanf("%d", &n);
    int** CantorMatrix = getCantorMatrix(n);
    printAnswer(CantorMatrix, n);
    fullFree(CantorMatrix, n);
    return 0;
}
