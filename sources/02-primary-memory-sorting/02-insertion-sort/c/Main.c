#include <stdio.h>

/**
 * Código fonte - Implementação do Método de Inserção
 *
 * @author Artur Bomtempo Colen
 * @algorithm Sorting
 * @type Insertion Sort
 * @language C
 * @version 1.0
 */

int numbersArray[] = {12, 4,  8, 2,  14, 17, 6,  18, 10,
                      16, 15, 5, 13, 9,  1,  11, 7,  3};
int n = 18;

void insertionSort() {
    for (int i = 1; i < n; i++) {
        int temp = numbersArray[i];
        int j = i - 1;

        while (j >= 0 && numbersArray[j] > temp) {
            numbersArray[j + 1] = numbersArray[j];
            j--;
        }

        numbersArray[j + 1] = temp;
    }
}

int main() {
    printf("Array original: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    insertionSort();

    printf("Array ordenado: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    return 0;
}