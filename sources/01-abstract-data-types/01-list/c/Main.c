#include <stdio.h>
#include <stdlib.h>

#define LENGTH 6

int array[LENGTH];
int n;

void start() {
    n = 0;
}

void insertStart(int value) {
    if (n >= LENGTH) {
        printf("Erro ao inserir dado na lista.\n");
        exit(1);
    }

    for (int i = n; i > 0; i--) {
        array[i] = array[i - 1];
    }

    array[0] = value;
    n++;
}

void insertEnd(int value) {
    if (n >= LENGTH) {
        printf("Erro ao inserir dado na lista.\n");
        exit(1);
    }

    array[n] = value;
    n++;
}

void insert(int value, int position) {
    if (n >= LENGTH || position < 0 || position > n) {
        printf("Erro ao inserir dado na lista.\n");
        exit(1);
    }

    for (int i = n; i > position; i--) {
        array[i] = array[i - 1];
    }

    array[position] = value;
    n++;
}

int removeStart() {
    if (n == 0) {
        printf("Erro ao remover dado da lista.\n");
        exit(1);
    }

    int valueRemoved = array[0];
    n--;

    for (int i = 0; i < n; i++) {
        array[i] = array[i + 1];
    }

    return valueRemoved;
}

int removeEnd() {
    if (n == 0) {
        printf("Erro ao remover dado da lista.\n");
        exit(1);
    }

    return array[--n];
}

int removeAt(int position) {
    if (n == 0 || position < 0 || position >= n) {
        printf("Erro ao remover dado da lista.\n");
        exit(1);
    }

    int valueRemoved = array[position];
    n--;

    for (int i = position; i < n; i++) {
        array[i] = array[i + 1];
    }

    return valueRemoved;
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
    printf("===== Lista Linear =====\n");

    start();
    int x1, x2, x3;

    insertStart(1);
    insertEnd(7);
    insertEnd(9);
    insertStart(3);
    insert(8, 3);
    insert(4, 2);

    show();

    x1 = removeStart();
    x2 = removeEnd();
    x3 = removeAt(2);

    printf("%d, %d, %d\n", x1, x2, x3);

    show();

    return 0;
}