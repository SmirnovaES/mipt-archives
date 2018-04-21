#include <stdio.h>
#include <stdlib.h>

double* getArray(int n) {
    double* array = (double*) malloc(sizeof(double)*n);
    int i;
    for (i = 0; i < n; i++) {
        scanf("%lf", &array[i]);
    }
    return array;
}

double getAverage(double* array, int n) {
    int i;
    double average = 0;
    for (i = 0; i < n; i++) {
        average += array[i];
    }
    return average / n;
}

double getAnswer(double* array, int n, double average) {
    int i;
    double answer = array[0];
    double min = abs(array[0] - average);
    for (i = 0; i < n; i++) {
        if (min > abs(array[i] - average)) {
            answer = array[i];
            min = abs(array[i] - average);
        }
    }
    return answer;
}

int main()
{
    int n;
    scanf("%d", &n);
    int* array = getArray(n);
    double average = getAverage(array, n);
    printf("%f", getAnswer(array, n, average));
    return 0;
}
