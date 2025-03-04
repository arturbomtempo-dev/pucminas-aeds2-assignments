#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Código fonte - Implementação da Lista Simples Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Flexible Singly Linked List
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

void insertStart(int value) {
    Cell *temp = newCell(value);

    temp->next = first->next;
    first->next = temp;

    if (first == last) {
        last = temp;
    }

    temp = NULL;
}

void insertEnd(int value) {
    last->next = newCell(value);
    last = last->next;
}

int removeStart() {
    if (first == last) {
        errx(1, "Erro ao remover elemento da lista.");
    }

    Cell *temp = first->next;
    first->next = first->next->next;

    int element = temp->element;

    temp->next = NULL;
    free(temp);
    temp = NULL;

    return element;
}

int removeEnd() {
    if (first == last) {
        errx(1, "Erro ao remover elemento da lista.");
    }

    Cell *i;

    for (i = first; i->next != last; i = i->next);

    int element = last->element;

    last = i;
    free(last->next);
    i = last->next = NULL;

    return element;
}

int length() {
    int length = 0;
    Cell *i;

    for (i = first; i != last; i = i->next, length++);

    return length;
}

void insert(int value, int position) {
    int len = length();

    if (position < 0 || position > len) {
        errx(1, "Erro ao inserir elemento na posição %d", position);
    } else if (position == 0) {
        insertStart(value);
    } else if (position == len) {
        insertEnd(value);
    } else {
        int j;
        Cell *i = first;

        for (j = 0; j < position; j++, i = i->next);

        Cell *temp = newCell(value);
        temp->next = i->next;
        i->next = temp;

        temp = i = NULL;
    }
}

int removal(int position) {
    int element, len = length();

    if (first == last) {
        errx(1, "Erro ao remover elemento da lista.");
    } else if (position < 0 || position > len) {
        errx(1, "Erro ao remover elemento na posição %d.", position);
    } else if (position == 0) {
        element = removeStart();
    } else if (position == len) {
        element = removeEnd();
    } else {
        Cell *i = first;
        int j;

        for (j = 0; j < position; j++, i = i->next);

        Cell *temp = i->next;

        element = temp->element;
        i->next = temp->next;

        temp->next = NULL;
        free(temp);
        i = temp = NULL;
    }

    return element;
}

void show() {
    printf("[ ");

    for (Cell *i = first->next; i != NULL; i = i->next) {
        printf("%d ", i->element);
    }

    printf("]\n");
}

bool search(int value) {
    bool found = false;

    for (Cell *i = first; i != NULL; i = i->next) {
        if (i->element == value) {
            found = true;
            i = last;
        }
    }

    return found;
}

int main() {
    int x1, x2, x3, x4, x5, x6;
    printf("=== Lista Dinâmica Simplesmente Encadeada === \n\n");

    start();

    insertStart(1);
    insertStart(0);
    insertEnd(4);
    insertEnd(5);
    insert(2, 2);
    insert(3, 3);
    insert(6, 6);
    insert(-1, 0);
    insertEnd(7);
    insertEnd(8);

    printf("Após inserções:\n");
    show();

    x1 = removal(3);
    x2 = removal(2);
    x3 = removeEnd();
    x4 = removeStart();
    x5 = removal(0);
    x6 = removal(4);

    printf("Após remoções (%d, %d, %d, %d, %d, %d):\n", x1, x2, x3, x4, x5, x6);
    show();

    return 0;
}