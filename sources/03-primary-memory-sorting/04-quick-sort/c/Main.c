#include <stdio.h>

/**
 * Código fonte - Implementação do Método Quicksort
 *
 * @author Artur Bomtempo Colen
 * @algorithm Sorting
 * @type Quick Sort
 * @language C
 * @version 1.0
 */

int numbersArray[] = {12, 4,  8, 2,  14, 17, 6,  18, 10,
                      16, 15, 5, 13, 9,  1,  11, 7,  3};
int n = 18;

void swap(int i, int j) {
    int temp = numbersArray[i];
    numbersArray[i] = numbersArray[j];
    numbersArray[j] = temp;
}

void quickSort(int left, int right) {
    int i = left, j = right;
    int pivot = numbersArray[(left + right) / 2];

    while (i <= j) {
        while (numbersArray[i] < pivot) {
            i++;
        }

        while (numbersArray[j] > pivot) {
            j--;
        }

        if (i <= j) {
            swap(i, j);
            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(left, j);
    }

    if (i < right) {
        quickSort(i, right);
    }
}

int main() {
    printf("Array original: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    quickSort(0, n - 1);

    printf("Array ordenado: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    return 0;
}