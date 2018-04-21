#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double polynom(double x) {
    double f = 2 * x + 1;
    return f;
}

int binsearch_solve(double (*f)(double), double a, double b, double *x, double epsilon, unsigned max_it) {
    static int flag = 1;
    if (max_it == 0) {
        flag = 0;
    } else {
        max_it--;
        double c = (b + a) / 2;
        double curr_f = (*f)(c);
        if (fabs(curr_f) < epsilon) {
            *x = c;
            return 1;
        } else if (curr_f > 0) {
            flag = binsearch_solve(*f, a, c, x, epsilon, max_it);
        } else {
            flag = binsearch_solve(*f, c, b, x, epsilon, max_it);
        }
    }
    return flag;
}

int main()
{
    double a = -5, b = 5;
    double solution, epsilon = 0.2;
    unsigned int max_it = 20;
    if (binsearch_solve(&polynom, a, b, &solution, epsilon, max_it) == 1) {
        printf("%f ", solution);
    } else {
        printf("error");
    }
    return 0;
}
