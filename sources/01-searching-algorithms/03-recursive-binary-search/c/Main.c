#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Código fonte - Implementação de Pesquisa Binária Recursiva
 *
 * @author Artur Bomtempo Colen
 * @algorithm Recursive Binary Search
 * @type Search Algorithm
 * @language C
 * @version 1.0
 */

int binarySearch(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    }

    if (arr[mid] < target) {
        return binarySearch(arr, mid + 1, right, target);
    } else {
        return binarySearch(arr, left, mid - 1, target);
    }
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
        int result = binarySearch(arr, 0, 9, target);

        if (result != -1) {
            printf("Valor %d encontrado no índice %d.\n", target, result);
        } else {
            printf("Valor %d não encontrado no vetor.\n", target);
        }
    }

    return 0;
}