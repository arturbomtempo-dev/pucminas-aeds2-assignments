#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Código fonte - Implementação da Pilha Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Flexible Stack
 * @language C
 * @version 1.0
 */

typedef struct Cell {
    int element;
    struct Cell *next;
} Cell;

Cell *top;

Cell *newCell(int element) {
    Cell *new = (Cell *)malloc(sizeof(Cell));
    new->element = element;
    new->next = NULL;
    return new;
}

void start() { top = NULL; }

void insert(int value) {
    Cell *temp = newCell(value);
    temp->next = top;
    top = temp;
    temp = NULL;
}

int removal() {
    if (top == NULL) {
        errx(1, "Erro ao remover elemento da pilha.");
    }

    int element = top->element;
    Cell *temp = top;

    top = top->next;
    temp->next = NULL;
    free(temp);
    temp = NULL;

    return element;
}

void show() {
    Cell *i;

    printf("[ ");

    for (i = top; i != NULL; i = i->next) {
        printf("%d ", i->element);
    }

    printf("]\n");
}

int main() {
    int x1, x2, x3;

    printf("=== Pilha Flexível ===\n\n");

    start();

    insert(1);
    insert(2);
    insert(3);
    insert(4);
    insert(5);

    printf("Após inserções:\n");
    show();

    x1 = removal();
    x2 = removal();
    x3 = removal();

    printf("Após as remoções de %d, %d, %d\n", x1, x2, x3);
    show();

    return 0;
}