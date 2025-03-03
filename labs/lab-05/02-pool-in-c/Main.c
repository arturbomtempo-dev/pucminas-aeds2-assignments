#include <stdio.h>

/**
 * LAB05Q01 - Sinuca em C
 *
 * @author Artur Bomtempo Colen
 * @version 1.0, 15/09/2024
 */

int main() {
    int N;

    scanf("%d", &N);

    int array[N];

    for (int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }

    while (N > 1) {
        for (int j = 0; j < N - 1; j++) {
            if (array[j] == array[j + 1]) {
                array[j] = 1;
            } else {
                array[j] = -1;
            }
        }

        N--;
    }

    if (array[0] == 1) {
        printf("preta\n");
    } else if (array[0] == -1) {
        printf("branca\n");
    }
}