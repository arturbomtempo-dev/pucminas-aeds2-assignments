#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Código fonte - Implementação da Fila Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Flexible Queue
 * @language C
 * @version 1.0
 */

typedef struct Cell {
    int element;
    struct Cell *next;
} Cell;

Cell *first, *last;

Cell *newCell(int element) {
    Cell *new = (Cell *)malloc(sizeof(Cell));
    new->element = element;
    new->next = NULL;
    return new;
}

void start() {
    first = newCell(0);
    last = first;
}

void insert(int value) {
    last->next = newCell(value);
    last = last->next;
}

int removal() {
    if (first == last) {
        errx(1, "Erro ao removal elemento da fila.");
    }

    Cell *temp = first->next;
    first->next = first->next->next;

    int element = temp->element;

    temp->next = NULL;
    free(temp);
    temp = NULL;

    return element;
}

void show() {
    Cell *i;

    printf("[ ");

    for (i = first->next; i != NULL; i = i->next) {
        printf("%d ", i->element);
    }

    printf("]\n");
}

int main() {
    int x1, x2, x3;
    printf("=== Fila Flexível ===\n");

    start();

    insert(5);
    insert(7);
    insert(8);
    insert(9);

    printf("\nApós inserções(5, 7, 8, 9):\n");
    show();

    x1 = removal();
    x2 = removal();

    printf("\nApós remoções (%d, %d):\n", x1, x2);
    show();

    insert(3);
    insert(4);

    printf("\nApós inserções(3, 4):\n");
    show();

    x1 = removal();
    x2 = removal();
    x3 = removal();

    printf("\nApós remoções (%d, %d, %d):\n", x1, x2, x3);
    show();

    insert(4);
    insert(5);

    printf("\nApós inserções(4, 5):\n");
    show();

    x1 = removal();
    x2 = removal();

    printf("\nApós remoções (%d, %d):\n", x1, x2);
    show();

    insert(6);
    insert(7);

    printf("\nApós inserções(6, 7):\n");
    show();

    x1 = removal();

    printf("\nApós remocao (%d):\n", x1);
    show();

    return 0;
}