#include <stdio.h>
#include <string.h>

/**
 * LAB01Q03 - Aquecimento Iterativo em C
 *
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/08/2024
 */

int checkCapitalLetters(char word[]) {
    int count = 0;

    for (int i = 0; i < strlen(word); i++) {
        char currentChar = word[i];

        if (currentChar >= 'A' && currentChar <= 'Z') {
            count++;
        }
    }

    return count;
}

int main() {
    char input[100];

    scanf(" %[^\n]", input);

    while (!(input[0] == 'F' && input[1] == 'I' && input[2] == 'M')) {
        int numCapitalLetters = checkCapitalLetters(input);
        printf("%d\n", numCapitalLetters);

        scanf(" %[^\n]", input);
    }

    return 0;
}