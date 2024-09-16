#include <stdio.h>
#include <string.h>

/**
 * LAB01Q03 - Aquecimento Iterativo em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/08/2024
 */

/**
 * Conta o número de letras maiúsculas na palavra fornecida.
 *
 * @param word a string de entrada a ser verificada quanto a letras maiúsculas.
 * @return o número de letras maiúsculas encontradas na string.
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

/**
 * Método principal que lê strings de entrada do usuário, conta o número de
 * letras maiúsculas em cada string e imprime o resultado. O programa é finalizado
 * quando o usuário insere a palavra "FIM".
 */
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