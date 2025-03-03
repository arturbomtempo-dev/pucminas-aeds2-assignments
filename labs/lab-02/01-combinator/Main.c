#include <stdio.h>
#include <string.h>

/**
 * LAB02Q01 - Combinador
 *
 * @author Artur Bomtempo Colen
 * @version 1.0, 25/08/2024
 */

int main() {
    char word1[100], word2[100];

    while (scanf("%s %s", word1, word2) != EOF) {
        int i = 0, j = 0;

        while (word1[i] != '\0' && word2[j] != '\0') {
            printf("%c", word1[i]);
            printf("%c", word2[j]);
            i++;
            j++;
        }

        while (word1[i] != '\0') {
            printf("%c", word1[i]);
            i++;
        }

        while (word2[j] != '\0') {
            printf("%c", word2[j]);
            j++;
        }

        printf("\n");
    }

    return 0;
}
