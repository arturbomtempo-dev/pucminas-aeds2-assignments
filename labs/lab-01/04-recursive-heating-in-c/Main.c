#include <stdio.h>
#include <string.h>

/**
 * LAB01Q04 - Aquecimento Recursivo em C
 *
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/08/2024
 */

int checkCapitalLetters(char word[], int index) {
    int count = 0;

    if (index < strlen(word)) {
        char currentChar = word[index];

        if (currentChar >= 'A' && currentChar <= 'Z') {
            count++;
        }

        count += checkCapitalLetters(word, index + 1);
    }

    return count;
}

int main() {
    char input[100];

    scanf(" %[^\n]", input);

    while (!(input[0] == 'F' && input[1] == 'I' && input[2] == 'M')) {
        int numCapitalLetters = checkCapitalLetters(input, 0);
        printf("%d\n", numCapitalLetters);

        scanf(" %[^\n]", input);
    }

    return 0;
}