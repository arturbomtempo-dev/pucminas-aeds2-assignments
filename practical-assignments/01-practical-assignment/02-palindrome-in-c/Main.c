#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * TP01Q02 - Palindromo em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1 29/08
 */

/**
 * Verifica se uma palavra é um palíndromo, percorrendo a palavra toda e verificando
 * se as letras do início e fim da palavra coincidem até terminar de percorrer toda.
 * 
 * @param word A palavra a ser verificada.
 * @return {@code true} se a palavra for um palíndromo, {@code false} caso contrário.
 */
int verifyPalindrome(char *word) {
    int isPalindrome = 1;

    for (int i = 0; i < strlen(word) / 2; i++) {
        if (word[i] != word[strlen(word) - 1 - i]) {
            isPalindrome = 0;
        }
    }

    return isPalindrome;
}

/**
 * Verifica se a palavra de entrada é "FIM", indicando o término da execução.
 * 
 * @param input A palavra de entrada a ser verificada.
 * @return {@code true} se a palavra for "FIM", {@code false} caso contrário.
 */
int isEnd(char *input) {
    return strlen(input) == 4 && input[0] == 'F' && input[1] == 'I' && input[2] == 'M' && input[3] == '\n';
}

/**
 * Método principal que lê palavras da entrada padrão, verifica se são palíndromos,
 * e para a execução quando "FIM" é digitado.
 */
int main() {
    char *word = (char *)malloc(1024 * sizeof(char));

    while (fgets(word, 1024, stdin) != NULL) {
        // Remover o caractere de nova linha, se presente
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