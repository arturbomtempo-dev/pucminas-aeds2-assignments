#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * TP01Q09 - Arquivo
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 31/08/2024
 */

int main() {
    int n;
    FILE *file;
    double value;
    long filePointer;

    scanf("%d", &n);

    file = fopen("file.txt", "w");

    for (int i = 0; i < n; i++) {
        scanf("%lf", &value);
        fwrite(&value, sizeof(double), 1, file);
    }

    fclose(file);

    file = fopen("file.txt", "r");

    fseek(file, 0, SEEK_END);
    filePointer = ftell(file);

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