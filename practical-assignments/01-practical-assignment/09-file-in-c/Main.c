#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * TP01Q09 - Arquivo
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 31/08/2024
 */

/**
 * Método principal do programa responsável por ler um número 
 * especificado de valores reais, grava-os em um arquivo e, em seguida, 
 * lê o arquivo na ordem inversa, imprimindo os valores sem a parte decimal 
 * se forem inteiros.
 */
int main() {
    int n;
    FILE *file;
    double value;
    long filePointer;

    scanf("%d", &n);

    // Abrindo o arquivo para escrita
    file = fopen("file.txt", "w");

    // Gravando os valores no arquivo
    for (int i = 0; i < n; i++) {
        scanf("%lf", &value);
        fwrite(&value, sizeof(double), 1, file);
    }

    fclose(file);

    file = fopen("file.txt", "r");

    // Movendo o ponteiro do arquivo para o final
    fseek(file, 0, SEEK_END);
    filePointer = ftell(file);

    // Lendo os valores do arquivo de trás para frente
    while (filePointer > 0) {
        filePointer -= sizeof(double);

        fseek(file, filePointer, SEEK_SET);
        fread(&value, sizeof(double), 1, file);

        if (value == floor(value)) {
            printf("%.0lf\n", value);
        } else {
            printf("%.15g\n", value);
        }
    }

    fclose(file);
    return 0;
}