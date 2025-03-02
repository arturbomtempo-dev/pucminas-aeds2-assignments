#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * TP01Q02 - Palindromo em C
 *
 * @author Artur Bomtempo Colen
 * @version 1.0, 29/08/2024 */

int verifyPalindrome(char *word) {
    int isPalindrome = 1;

    for (int i = 0; i < strlen(word) / 2; i++) {
        if (word[i] != word[strlen(word) - 1 - i]) {
            isPalindrome = 0;
        }
    }

    return isPalindrome;
}

int isEnd(char *input) {
    return strlen(input) == 4 && input[0] == 'F' && input[1] == 'I' &&
           input[2] == 'M' && input[3] == '\n';
}

int main() {
    char *word = (char *)malloc(1024 * sizeof(char));

    while (fgets(word, 1024, stdin) != NULL) {
        if (strlen(word) > 0 && word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }

        if (!isEnd(word)) {
            int wordIsPalindrome = verifyPalindrome(word);

            if (wordIsPalindrome) {
                printf("SIM\n");
            } else {
                printf("NAO\n");
            }
        }
    }

    free(word);

    return 0;
}