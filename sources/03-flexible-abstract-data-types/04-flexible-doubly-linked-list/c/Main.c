#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Código fonte - Implementação da Lista Dupla Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Flexible Doubly Linked List
 * @language C
 * @version 1.0
 */

typedef struct DoubleCell {
    int element;
    struct DoubleCell *next, *previous;
} DoubleCell;

DoubleCell *first, *last;

DoubleCell *newDoubleCell(int element) {
    DoubleCell *new = (DoubleCell *)malloc(sizeof(DoubleCell));
    new->element = element;
    new->next = new->previous = NULL;
    return new;
}

void start() {
    first = newDoubleCell(0);
    last = first;
}

void insertStart(int value) {
    DoubleCell *temp = newDoubleCell(value);

    temp->previous = first;
    temp->next = first->next;
    first->next = temp;

    if (first == last) {
        last = temp;
    } else {
        temp->next->previous = temp;
    }

    temp = NULL;
}

void insertEnd(int value) {
    last->next = newDoubleCell(value);
    last->next->previous = last;
    last = last->next;
}

int removeStart() {
    if (first == last) {
        errx(1, "Erro ao remover elemento da lista.");
    }

    DoubleCell *temp = first->next;
    first->next = temp->next;
    first->next->previous = first;

    int element = temp->element;

    temp->next = temp->previous = NULL;
    free(temp);

    return element;
}

int removeEnd() {
    if (first == last) {
        errx(1, "Erro ao remover elemento da lista.");
    }

    int element = last->element;

    last = last->previous;
    last->next->previous = NULL;
    free(last->next);
    last->next = NULL;

    return element;
}

int length() {
    int length = 0;
    DoubleCell *i;

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
        DoubleCell *i = first;

        for (j = 0; j < position; j++, i = i->next);

        DoubleCell *temp = newDoubleCell(value);

        temp->previous = i;
        temp->next = i->next;
        temp->previous->next = temp->next->previous = temp;

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
        DoubleCell *i = first;
        int j;

        for (j = 0; j < position; j++, i = i->next);

        i->previous->next = i->next;
        i->next->previous = i->previous;

        element = i->element;

        i->next = i->previous = NULL;
        free(i);
        i = NULL;
    }

    return element;
}

void show() {
    printf("[ ");

    for (DoubleCell *i = first->next; i != NULL; i = i->next) {
        printf("%d ", i->element);
    }

    printf("]\n");
}

void showReverse() {
    printf("[ ");

    for (DoubleCell *i = last; i != first; i = i->previous) {
        printf("%d ", i->element);
    }

    printf("]\n");
}

bool search(int value) {
    bool found = false;

    for (DoubleCell *i = first; i != NULL; i = i->next) {
        if (i->element == value) {
            found = true;
            i = last;
        }
    }

    return found;
}

int main() {
    printf("=== Lista Dinâmica Duplamente Encadeada === \n\n");

    start();

    insertStart(2);
    insertStart(1);
    insertEnd(5);
    insertEnd(6);
    insert(3, 2);
    insert(4, 3);
    insert(7, 6);
    insert(0, 0);
    insertEnd(8);
    insertEnd(9);

    printf("Após inserções:\n");
    show();
    showReverse();

    removal(3);
    removal(2);
    removeEnd();
    removeStart();
    removal(0);
    removal(4);

    printf("Após remoções:\n");
    show();
    showReverse();

    return 0;
}