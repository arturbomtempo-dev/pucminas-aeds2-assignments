#include <stdio.h>
#include <stdlib.h>

#define LENGTH 6

int array[LENGTH];
int first = 0;
int last = 0;

void insertItem(int value) {
    if (((last + 1) % LENGTH) == first) {
        printf("Erro ao inserir dado na fila.\n");
        exit(1);
    }

    array[last] = value;
    last = (last + 1) % LENGTH;
}

int removeItem() {
    if (first == last) {
        printf("Erro ao removeItemr dado da fila.\n");
        exit(1);
    }

    int valueRemoveItemd = array[first];
    first = (first + 1) % LENGTH;
    return valueRemoveItemd;
}

void show() {
    printf("[");

    for (int i = first; i != last; i = (i + 1) % LENGTH) {
        printf("%d", array[i]);
        if ((i + 1) % LENGTH != last) {
            printf(", ");
        }
    }

    printf("]\n");
}

int main() {
    printf("===== Fila Circular =====\n");

    int x1, x2, x3;

    insertItem(1);
    insertItem(7);
    insertItem(9);
    insertItem(8);
    insertItem(4);

    show();

    x1 = removeItem();
    x2 = removeItem();
    x3 = removeItem();

    printf("Removidos: %d, %d, %d\n", x1, x2, x3);

    show();

    insertItem(5);
    insertItem(6);

    show();

    return 0;
}