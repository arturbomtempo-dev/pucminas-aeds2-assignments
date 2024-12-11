#include <stdio.h>
#include <string.h>

/**
 * BEE 1244
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 27/10/2024
 */

void bubbleSort(char arr[][51], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strlen(arr[j]) < strlen(arr[j + 1])) {
                char temp[51];

                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        char strings[50][51];
        int count = 0;

        while (scanf("%s", strings[count])) {
            count++;

            if (getchar() == '\n') {
                break;
            }
        }

        bubbleSort(strings, count);

        for (int j = 0; j < count; j++) {
            printf("%s", strings[j]);
            
            if (j < count - 1) {
                printf(" ");
            }
        }

        printf("\n");
    }

    return 0;
}