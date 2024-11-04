#include <stdio.h>

int numbersArray[] = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
int n = 18;

void swap(int i, int j) {
    int temp = numbersArray[i];
    numbersArray[i] = numbersArray[j];
    numbersArray[j] = temp;
}

void selectionSort() {
    for (int i = 0; i < n - 1; i++) {
        int smallest = i;

        for (int j = i + 1; j < n; j++) {
            if (numbersArray[smallest] > numbersArray[j]) {
                smallest = j;
            }
        }

        swap(smallest, i);
    }
}

int main() {
    printf("Array original: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    selectionSort();

    printf("Array ordenado: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }
    
    printf("\n");

    return 0;
}