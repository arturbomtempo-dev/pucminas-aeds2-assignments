#include <stdio.h>
#include <string.h>

/**
 * BEE 1244
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 27/10/2024
 */

/**
 * Realiza a ordenação de um array de strings em ordem decrescente de tamanho.
 * Utiliza o algoritmo Bubble Sort para comparar o comprimento de cada string
 * e realizar trocas de posição entre elas, quando necessário.
 *
 * @param arr Array de strings que será ordenado.
 * @param n Quantidade de strings no array.
 */
void bubbleSort(char arr[][51], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strlen(arr[j]) < strlen(arr[j + 1])) {
                char temp[51];

                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

/**
 * Função principal que executa a leitura e ordenação de múltiplas listas de strings.
 * Para cada lista, lê as strings da entrada padrão, ordena-as em ordem decrescente
 * de tamanho usando a função bubbleSort e exibe o resultado.
 */
int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        char strings[50][51];
        int count = 0;

        while (scanf("%s", strings[count])) {
            count++;

            if (getchar() == '\n') {
                break;
            }
        }

        bubbleSort(strings, count);

        for (int j = 0; j < count; j++) {
            printf("%s", strings[j]);
            
            if (j < count - 1) {
                printf(" ");
            }
        }

        printf("\n");
    }

    return 0;
}