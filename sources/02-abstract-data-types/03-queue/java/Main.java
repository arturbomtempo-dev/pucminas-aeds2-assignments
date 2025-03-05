/**
 * Código fonte - Implementação de Fila
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Queue
 * @language Java
 * @version 1.0
 */

class Queue {
    private static final int LENGTH = 6;
    private static int[] array = new int[LENGTH];
    private static int front = -1;
    private static int rear = -1;

    public static void start() {
        front = rear = -1;
    }

    public static boolean isFull() {
        return rear == LENGTH - 1;
    }

    public static boolean isEmpty() {
        return front == -1;
    }

    public static void enqueue(int value) {
        if (isFull()) {
            System.out.println("Erro: Fila cheia.");
            System.exit(1);
        }

        if (front == -1) {
            front = 0;
        }

        rear++;
        array[rear] = value;
    }

    public static int dequeue() {
        if (isEmpty()) {
            System.out.println("Erro: Fila vazia.");
            System.exit(1);
        }

        int value = array[front];

        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }

        return value;
    }

    public static void show() {
        if (isEmpty()) {
            System.out.println("Fila vazia.");
            return;
        }

        System.out.print("Fila: [");

        for (int i = front; i <= rear; i++) {
            System.out.print(array[i]);

            if (i < rear) {
                System.out.print(", ");
            }
        }

        System.out.println("]");
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("===== Fila =====");

        Queue.start();

        Queue.enqueue(1);
        Queue.enqueue(7);
        Queue.enqueue(9);
        Queue.enqueue(3);
        Queue.enqueue(8);
        Queue.enqueue(4);

        Queue.show();

        int x1 = Queue.dequeue();
        int x2 = Queue.dequeue();
        int x3 = Queue.dequeue();

        System.out.println(x1 + ", " + x2 + ", " + x3);

        Queue.show();
    }
}