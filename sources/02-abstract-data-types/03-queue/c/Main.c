#include <stdio.h>
#include <stdlib.h>

/**
 * Código fonte - Implementação de Fila
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Queue
 * @language C
 * @version 1.0
 */

#define LENGTH 6

int array[LENGTH];
int front = -1;
int rear = -1;

void start() { front = rear = -1; }

int isFull() { return rear == LENGTH - 1; }

int isEmpty() { return front == -1; }

void enqueue(int value) {
    if (isFull()) {
        printf("Erro: Fila cheia.\n");
        exit(1);
    }

    if (front == -1) {
        front = 0;
    }

    rear++;
    array[rear] = value;
}

int dequeue() {
    if (isEmpty()) {
        printf("Erro: Fila vazia.\n");
        exit(1);
    }

    int value = array[front];

    if (front == rear) {
        front = rear = -1;
    } else {
        front++;
    }

    return value;
}

void show() {
    if (isEmpty()) {
        printf("Fila vazia.\n");
        return;
    }

    printf("Fila: [");

    for (int i = front; i <= rear; i++) {
        printf("%d", array[i]);

        if (i < rear) {
            printf(", ");
        }
    }

    printf("]\n");
}

int main() {
    printf("===== Fila =====\n");

    start();

    enqueue(1);
    enqueue(7);
    enqueue(9);
    enqueue(3);
    enqueue(8);
    enqueue(4);

    show();

    int x1 = dequeue();
    int x2 = dequeue();
    int x3 = dequeue();

    printf("%d, %d, %d\n", x1, x2, x3);

    show();

    return 0;
}