#include <stdio.h>

/**
 * Código fonte - Implementação do Método Radix Sort
 *
 * @author Artur Bomtempo Colen
 * @algorithm Sorting
 * @type Radix Sort
 * @language C
 * @version 1.0
 */

static int numbersArray[] = {12, 4,  8, 2,  14, 17, 6,  18, 10,
                             16, 15, 5, 13, 9,  1,  11, 7,  3};
static int n = 18;

int getBiggestNumber() {
    int biggest = numbersArray[0];

    for (int i = 1; i < n; i++) {
        if (numbersArray[i] > biggest) {
            biggest = numbersArray[i];
        }
    }

    return biggest;
}

void countingSort(int exp) {
    int count[10] = {0};
    int sorted[n];

    for (int i = 0; i < n; i++) {
        count[(numbersArray[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        sorted[count[(numbersArray[i] / exp) % 10] - 1] = numbersArray[i];
        count[(numbersArray[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        numbersArray[i] = sorted[i];
    }
}

void radixSort() {
    int max = getBiggestNumber();

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(exp);
    }
}

int main() {
    printf("Array original:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    radixSort();

    printf("Array ordenado:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    return 0;
}