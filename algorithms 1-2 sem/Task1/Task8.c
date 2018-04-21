#include <stdio.h>
#include <stdlib.h>

double* getArray(int n) {
    double* array = (double*) malloc(sizeof(double)*n);
    printf("Enter %d numbers:\n", n);
    int i;
    for (i = 0; i < n; i++) {
        scanf("%lf", &array[i]);
    }
    return array;
}

double sumKohan (double* array, int n) {
    double sum = 0;
    double c = 0;
    int i;
    for (i = 0; i < n; i++) {
        double y = array[i] - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

double sumNormal (double* array, int n) {
    double sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {
    printf("Enter the amount of numbers:\n");
    int n;
    scanf("%d", &n);
    double* array = getArray(n);
    double sum1 = sumKohan(array, n);
    double sum2 = sumNormal(array, n);
    printf("The Kohan sum and normal sum are:\n%.10f\n%.10f\n", sum1, sum2);
    free(array);
    return 0;
}
