#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Código fonte - Implementação de Pesquisa Sequencial
 *
 * @author Artur Bomtempo Colen
 * @algorithm Sequential Search
 * @type Search Algorithm
 * @language C
 * @version 1.0
 */

#define SIZE 10

int sequentialSearch(int array[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }

    return -1;
}

void generateRandomArray(int array[], int size) {
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100 + 1;
    }
}

void printArray(int array[], int size) {
    printf("[ ");

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    printf("]\n");
}

int main() {
    int array[SIZE];
    generateRandomArray(array, SIZE);
    printArray(array, SIZE);

    int searchTargets[] = {30, 50, 75, 15};
    int numTests = sizeof(searchTargets) / sizeof(searchTargets[0]);

    for (int i = 0; i < numTests; i++) {
        int target = searchTargets[i];
        printf("\nProcurando pelo valor %d...\n", target);
        
        int result = sequentialSearch(array, SIZE, target);

        if (result != -1) {
            printf("Valor %d encontrado no índice %d.\n", target, result);
        } else {
            printf("Valor %d não encontrado no vetor.\n", target);
        }
    }

    return 0;
}