#include <stdio.h>

/**
 * BEE 1382
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 06/11/2024
 */

void swap(int array[], int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int selectionSort(int array[], int n) {
    int movements = 0;

    for (int i = 0; i < n; i++) {
        int smallest = i;

        for (int j = i + 1; j < n; j++) {
            if (array[smallest] > array[j]) {
                swap(array, smallest, j);
                movements++;
            }
        }
    }

    return movements;
}

int main() {
    int numberInstances;

    scanf("%d", &numberInstances);

    for (int i = 0; i < numberInstances; i++) {
        int sequenceLength;
        scanf("%d", &sequenceLength);

        int sequence[sequenceLength];

        for (int j = 0; j < sequenceLength; j++) {
            scanf("%d", &sequence[j]);
        }

        int movements = selectionSort(sequence, sequenceLength);

        printf("%d\n", movements);
    }

    return 0;
}