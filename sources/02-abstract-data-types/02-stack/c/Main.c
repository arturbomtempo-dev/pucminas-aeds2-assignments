#include <stdio.h>
#include <stdlib.h>

/**
 * Código fonte - Implementação de Pilha
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Stack
 * @language C
 * @version 1.0
 */

#define LENGTH 6

int array[LENGTH];
int n;

void start() { n = 0; }

void push(int value) {
    if (n >= LENGTH) {
        printf("Erro ao inserir dado na pilha.\n");
        exit(1);
    }

    array[n] = value;
    n++;
}

int pop() {
    if (n == 0) {
        printf("Erro ao remover dado da pilha.\n");
        exit(1);
    }

    return array[--n];
}

int peek() {
    if (n == 0) {
        printf("Pilha vazia.\n");
        exit(1);
    }

    return array[n - 1];
}

void show() {
    printf("[");

    for (int i = 0; i < n; i++) {
        printf("%d", array[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }

    printf("]\n");
}

int main() {
    printf("===== Pilha =====\n");

    start();
    int x1, x2, x3;

    push(1);
    push(7);
    push(9);
    push(3);
    push(8);
    push(4);

    show();

    x1 = pop();
    x2 = pop();
    x3 = pop();

    printf("%d, %d, %d\n", x1, x2, x3);

    show();

    return 0;
}