#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1;
    }
}

void printArray(int arr[], int size) {
    printf("[ ");

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("]\n");
}

int main() {
    srand(time(0));

    int arr[10];
    generateRandomArray(arr, 10);
    qsort(arr, 10, sizeof(int), (int (*)(const void *, const void *))strcmp);
    printArray(arr, 10);

    int targets[] = {30, 50, 75, 15};

    for (int i = 0; i < 4; i++) {
        int target = targets[i];
        printf("\nProcurando pelo valor %d...\n", target);
        
        int result = binarySearch(arr, 10, target);

        if (result != -1) {
            printf("Valor %d encontrado no índice %d.\n", target, result);
        } else {
            printf("Valor %d não encontrado no vetor.\n", target);
        }
    }

    return 0;
}