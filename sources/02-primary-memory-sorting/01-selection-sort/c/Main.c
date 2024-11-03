#include <stdio.h>

void swap(int *numbersArray, int i, int j) {
    int temp = numbersArray[i];
    numbersArray[i] = numbersArray[j];
    numbersArray[j] = temp;
}

void selectionSort(int *numbersArray, int n) {
    for (int i = 0; i < n - 1; i++) {
        int smallest = i;

        for (int j = i + 1; j < n; j++) {
            if (numbersArray[smallest] > numbersArray[j]) {
                smallest = j;
            }
        }

        swap(numbersArray, smallest, i);
    }
}

int main() {
    int numbers[] = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };

    printf("Array original: ");

    for (int i = 0; i < 18; i++) {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    selectionSort(numbers, 18);

    printf("Array ordenado: ");

    for (int i = 0; i < 18; i++) {
        printf("%d ", numbers[i]);
    }
    
    printf("\n");

    return 0;
}