#include <stdio.h>

void insertionSort(int *numbersArray, int n) {
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
    int numbers[] = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };

    printf("Array original: ");

    for (int i = 0; i < 18; i++) {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    insertionSort(numbers, 18);

    printf("Array ordenado: ");

    for (int i = 0; i < 18; i++) {
        printf("%d ", numbers[i]);
    }
    
    printf("\n");

    return 0;
}