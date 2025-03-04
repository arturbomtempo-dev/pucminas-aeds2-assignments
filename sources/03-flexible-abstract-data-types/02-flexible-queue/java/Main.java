/**
 * Código fonte - Implementação da Fila Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Flexible Queue
 * @language Java
 * @version 1.0
 */

class Cell {
    public int element;
    public Cell next;

    public Cell() {
        this.element = 0;
        this.next = null;
    }

    public Cell(int value) {
        this.element = value;
        this.next = null;
    }
}

class Queue {
    private Cell first, last;

    public Queue() {
        first = new Cell();
        last = first;
    }

    public void inser(int value) {
        last.next = new Cell(value);
        last = last.next;
    }

    public int remove() {
        if (first == last) {
            throw new Error("Não foi possível remover um valor da fila.");
        }

        Cell temp = first.next;
        first.next = first.next.next;

        int element = temp.element;

        temp.next = null;
        temp = null;

        return element;
    }

    public void show() {
        System.out.print("[");

        for (Cell i = first.next; i != null; i = i.next) {
            System.out.print(i.element + " ");
        }

        System.out.print("]");
    }
}

public class Main {
    public static void main(String[] args) {
        Queue flexibleQueue = new Queue();

        flexibleQueue.inser(3);
        flexibleQueue.inser(5);
        flexibleQueue.inser(7);

        flexibleQueue.show();

        flexibleQueue.remove();
        flexibleQueue.remove();

        System.out.println();
        flexibleQueue.show();
    }
}