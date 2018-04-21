#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int i;
    int j;
} answer;

int* getArray(int n) {
    int* array = (int*) malloc(sizeof(int)*n);
    printf("Enter %d numbers:\n", n);
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    return array;
}

answer getCoordinates(int* data, int n) {
    assert(data != NULL && n != 0);
    answer ans;
    int* firstCoordinates = (int*) malloc(sizeof(int)*n);
    int* longestSubValues = (int*) malloc(sizeof(int)*n);
    int i;
    firstCoordinates[0] = 0;
    longestSubValues[0] = data[0];
    for (i = 0; i < n - 1; i++) {
        if (longestSubValues[i] < 0) {
            longestSubValues[i + 1] = data[i + 1];
            firstCoordinates[i + 1] = i + 1;
        } else {
            longestSubValues[i + 1] = longestSubValues[i] + data[i + 1];
            firstCoordinates[i + 1] = firstCoordinates[i];
        }
    }
    int curr_max = longestSubValues[0];
    ans.i = 0;
    ans.j = 0;
    for (i = 0; i < n; i++) {
        if (longestSubValues[i] > curr_max) {
            curr_max = longestSubValues[i];
            ans.i = firstCoordinates[i];
            ans.j = i;
        }
    }
    free(firstCoordinates);
    free(longestSubValues);
    return ans;
}

int main() {
    int n;
    printf("Enter the array's size:\n");
    scanf("%d", &n);
    int* array = getArray(n);
    answer ans = getCoordinates(array, n);
    printf("The answer is i=%d and j=%d.\n", ans.i, ans.j);
    free(array);
    return 0;
}
