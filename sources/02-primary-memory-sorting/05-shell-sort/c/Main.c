#include <stdio.h>

int numbersArray[] = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
int n = 18;

void colorInsertion(int color, int h) {
    for (int i = (color + h); i < n; i += h) {
        int temp = numbersArray[i];
        int j = i - h;

        while ((j >= 0) && (numbersArray[j] > temp)) {
            numbersArray[j + h] = numbersArray[j];
            j -= h;
        }

        numbersArray[j + h] = temp;
    }
}

void shellSort() {
    int h = 1;

    do {
        h = (h * 3) + 1;
    } while (h < n);

    do {
        h /= 3;

        for (int color = 0; color < h; color++) {
            colorInsertion(color, h);
        }
    } while (h != 1);
}

int main() {
    printf("Array original: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }

    printf("\n");

    shellSort();

    printf("Array ordenado: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", numbersArray[i]);
    }
    
    printf("\n");

    return 0;
}