#include <stdio.h>
#include <string.h>

/**
 * LAB01Q04 - Aquecimento Recursivo em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/08/2024
 */

/**
 * Conta o número de letras maiúsculas de forma recursiva.
 *
 * @param word  a string de entrada a ser verificada.
 * @param index o índice atual que está sendo verificado.
 * @return o número de letras maiúsculas encontradas até o momento.
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

/**
 * Método principal que lê strings de entrada do usuário, conta o número de
 * letras maiúsculas em cada string de forma recursiva e imprime o resultado.
 * O programa é finalizado quando o usuário insere a palavra "FIM".
 */
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