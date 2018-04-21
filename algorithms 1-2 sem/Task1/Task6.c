#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int i;
    int j;
} answer;

int* getArray (int n) {
    int* array = (int*) malloc(sizeof(int)*n);
    printf("Enter %d numbers:\n", n);
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    return array;
}

answer getCoordinates(int* array, int n) {
    answer ans;
    ans.i = 0;
    ans.j = n - 1;
    int curr_max = 0;
    int curr_i = 0, curr_j = 0;
    int max = 0;
    int i;
    for (i = 0; i < n - 1; i++) {
        if (array[i] <= array[i + 1]) {
            curr_max++;
            curr_j++;
        } else {
            if (curr_max > max) {
                max = curr_max;
                ans.i = curr_i;
                ans.j = curr_j;
            }
            curr_i = i + 1;
            curr_max = 0;
        }
        if (i == n - 2 && array[i] <= array[i + 1] && curr_max > max) {
            ans.i = curr_i;
            ans.j = n - 1;
        }
    }
    return ans;
}

int main()
{
    int n;
    printf("Enter the array's size:\n");
    scanf("%d", &n);
    int* array = getArray(n);
    answer ans = getCoordinates(array, n);
    printf("The answer is i=%d and j=%d.\n", ans.i, ans.j);
    free(array);
    return 0;
}
