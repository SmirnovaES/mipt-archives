#include <stdio.h>
#include <stdlib.h>

int* getCoeffs(int n) {
    int* coeffs = (int*) malloc(sizeof(int)*(n));
    printf("Enter the coefficients from a0 to an");
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &coeffs[i]);
    }
    return coeffs;
}

int getValue(int n, int x0, int* coeffs) {
    int answer = 0;
    int i;
    for (i = n; i >= 0; i--) {
            answer = coeffs[i] + answer*x0;
    }
    return answer;
}

int main() {
    printf("Enter the x0 dot and the degree of the polynom");
    int x0;
    int n;
    scanf("%d %d", &x0, &n);
    int* coeffs = getCoeffs(n + 1);
    int value = getValue(n, x0, coeffs);
    printf("The value of the polynom is %d. \n", value);
    free(coeffs);
    return 0;
}
