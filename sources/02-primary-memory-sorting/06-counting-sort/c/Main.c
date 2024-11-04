#include <stdio.h>

int numbersArray[] = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
int n = 18;

int getBiggestNumber() {
    int biggest = numbersArray[0];

    for (int i = 1; i < n; i++) {
        if (numbersArray[i] > biggest) {
            biggest = numbersArray[i];
        }
    }

    return biggest;
}

void countingSort(int *sorted) {
    int biggest = getBiggestNumber();
    int count[biggest + 1];

    for (int i = 0; i <= biggest; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        count[numbersArray[i]]++;
    }

    for (int i = 1; i <= biggest; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        sorted[count[numbersArray[i]] - 1] = numbersArray[i];
        count[numbersArray[i]]--;
    }
}

int main() {
    int sortedArray[n];

    printf("Array original:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    countingSort(sortedArray);

    printf("Array ordenado:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", sortedArray[i]);
    }
    
    printf("\n");

    return 0;
}