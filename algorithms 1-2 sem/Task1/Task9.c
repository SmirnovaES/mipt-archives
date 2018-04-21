#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double getSumFromMin(int n) {
    double sum = 0;
    int i;
    for (i = 1; i <= n; i++) {
        double c = 1.0 / i;
        c /= i;
        sum += c;
    }
    return sum;
}

double getSumFromMax(int n) {
    double sum = 0;
    int i;
    for (i = n; i >= 1; i--) {
        double c = 1.0 / i;
        c /= i;
        sum += c;
    }
    return sum;
}

int main() {
    printf("Enter the amount of numbers in a row:\n");
    int n;
    scanf("%d", &n);
    double sum1 = getSumFromMin(n);
    double sum2 = getSumFromMax(n);
    printf("Sums from minimal number and from maximal are:\n%.20f\n%.20f\n", sum1, sum2);
    double answer = M_PI*M_PI / 6;
    printf("The difference between true answer and sums is: \n%.20f for the first sum, \n%.20f for the second sum.", answer - sum1, answer - sum2);
    return 0;
}
