#include <stdio.h>

int numbersArray[] = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
int n = 18;

void bubbleSort() {
    int swapOccurred = 1;

    for (int rep = 0; rep < n - 1 && swapOccurred; rep++) {
        swapOccurred = 0;

        for (int b = 0; b < n - (rep + 1); b++) {
            if (numbersArray[b] > numbersArray[b + 1]) {
                int temp = numbersArray[b];
                numbersArray[b] = numbersArray[b + 1];
                numbersArray[b + 1] = temp;
                swapOccurred = 1;
            }
        }
    }
}

int main() {
    printf("Array original: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    bubbleSort();

    printf("Array ordenado: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }
    
    printf("\n");

    return 0;
}