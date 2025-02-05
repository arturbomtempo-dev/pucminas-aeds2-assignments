#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * TP01Q11 - RECURSIVO - Palíndromo em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 29/08/2024
 */

int verifyPalindrome(char *word, int left, int right) {
    int isPalindrome = 1;

    if (word[left] != word[right]) {
        isPalindrome = 0;
    } else if (left < right) {
        isPalindrome = verifyPalindrome(word, left + 1, right - 1);
    }

    return isPalindrome;
}

int isEnd(char *input) {
    return strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' && input[2] == 'M';
}

int main() {
    char *word = (char *)malloc(1024 * sizeof(char));

    while (fgets(word, 1024, stdin) != NULL) {
        if (strlen(word) > 0 && word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }

        if (!isEnd(word)) {
            int wordIsPalindrome = verifyPalindrome(word, 0, strlen(word) - 1);

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