#include <stdio.h>
#include <string.h>

/**
 * BEE 2150
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 17/09/2024
 */

int main() {
    char vowels[20], expression[100];

    while (scanf("%s", vowels) != EOF) {
        int vowelsCount = 0;
        scanf(" %[^\n]", expression);

        for (int i = 0; i < strlen(expression); i++) {
            char currentChar = expression[i];

            for (int j = 0; j < strlen(vowels); j++) {
                if (currentChar == vowels[j]) {
                    vowelsCount++;
                }
            }
        }

        printf("%d\n", vowelsCount);
    }

    return 0;
}