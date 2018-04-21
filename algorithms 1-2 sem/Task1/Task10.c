#include <stdio.h>
#include <stdlib.h>


double getDiameter(int* coordinates, int n) {
    int i, j;
    double max = 0;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            double dist = sqrt(pow(coordinates[2*i]-coordinates[2*j], 2) + pow(coordinates[2*i + 1] - coordinates[2*j + 1], 2));
            if (dist > max) {
                max = dist;
            }
        }
    }
    return max;
}

int* getArray(int n) {
    printf("Enter %d numbers -- each two are coordinates of 1 dot:\n", n);
    int* array = (int*) malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    return array;
}

int main()
{
    printf("Enter the amount of dots:\n");
    int n;
    scanf("%d", &n);
    int* coordinates = getArray(2*n);
    double answer = getDiameter(coordinates, n);
    printf("The diameter is %f.", answer);
    free(coordinates);
    return 0;
}
