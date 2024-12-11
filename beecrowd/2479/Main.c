#include <stdio.h>
#include <string.h>

/**
 * BEE 2479
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/09/2024
 */

int main() {
    int N, positiveCount = 0, negativeCount = 0;
    char digit, name[20];

    scanf("%d", &N);

    char namesArray[N][20];

    for (int i = 0; i < N; i++) {
        scanf(" %c %[^\n]", &digit, name);

        if (digit == '+') {
            positiveCount++;
        } else if (digit == '-') {
            negativeCount++;
        }

        int j = 0;

        while (name[j] != '\0' && j < 20) {
            namesArray[i][j] = name[j];
            j++;
        }

        namesArray[i][j] = '\0';
    }

    for (int i = 0; i < N - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < N; j++) {
            if (strcmp(namesArray[j], namesArray[minIndex]) < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            char temp[20];
            strcpy(temp, namesArray[i]);
            strcpy(namesArray[i], namesArray[minIndex]);
            strcpy(namesArray[minIndex], temp);
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%s\n", namesArray[i]);
    }

    printf("Se comportaram: %d | Nao se comportaram: %d\n", positiveCount, negativeCount);

    return 0;
}