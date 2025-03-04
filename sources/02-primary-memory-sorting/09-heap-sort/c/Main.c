#include <stdio.h>

/**
 * Código fonte - Implementação do Método Heap Sort
 *
 * @author Artur Bomtempo Colen
 * @algorithm Sorting
 * @type Heap Sort
 * @language C
 * @version 1.0
 */

static int numbersArray[] = {12, 4,  8, 2,  14, 17, 6,  18, 10,
                             16, 15, 5, 13, 9,  1,  11, 7,  3};
static int n = 18;

void swap(int i, int j) {
    int temp = numbersArray[i];
    numbersArray[i] = numbersArray[j];
    numbersArray[j] = temp;
}

int getBiggerSon(int i, int length) {
    int son = 2 * i;

    if (son + 1 < length && numbersArray[son] < numbersArray[son + 1]) {
        son++;
    }

    return son < length ? son : -1;
}

int hasSon(int i, int length) { return (2 * i < length); }

void rebuildHeap(int i, int length) {
    while (hasSon(i, length)) {
        int son = getBiggerSon(i, length);

        if (son != -1 && numbersArray[i] < numbersArray[son]) {
            swap(i, son);
            i = son;
        } else {
            i = length;
        }
    }
}

void buildHeap(int length) {
    for (int i = length / 2; i >= 1; i--) {
        rebuildHeap(i, length);
    }
}

void heapSort() {
    buildHeap(n);

    int length = n - 1;

    while (length > 0) {
        swap(1, length--);
        rebuildHeap(1, length + 1);
    }
}

int main() {
    printf("Array original:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    heapSort();

    printf("Array ordenado:\n");

    for (int i = 1; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    return 0;
}