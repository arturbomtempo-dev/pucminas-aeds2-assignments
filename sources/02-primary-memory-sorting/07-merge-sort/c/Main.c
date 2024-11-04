#include <stdio.h>
#include <limits.h>

int numbersArray[] = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
int n = 18;

void interleave(int left, int middle, int right) {
    int numbersLeft = middle - left + 1;
    int numbersRight = right - middle;

    int leftArray[numbersLeft + 1];
    int rightArray[numbersRight + 1];

    for (int i = 0; i < numbersLeft; i++) {
        leftArray[i] = numbersArray[left + i];
    }

    for (int j = 0; j < numbersRight; j++) {
        rightArray[j] = numbersArray[middle + 1 + j];
    }

    leftArray[numbersLeft] = INT_MAX;
    rightArray[numbersRight] = INT_MAX;

    int i = 0, j = 0;

    for (int k = left; k <= right; k++) {
        if (leftArray[i] <= rightArray[j]) {
            numbersArray[k] = leftArray[i++];
        } else {
            numbersArray[k] = rightArray[j++];
        }
    }
}

void mergeSort(int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;

        mergeSort(left, middle);
        mergeSort(middle + 1, right);
        interleave(left, middle, right);
    }
}

int main() {
    printf("Array original:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    mergeSort(0, n - 1);

    printf("Array ordenado:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }
    
    printf("\n");

    return 0;
}