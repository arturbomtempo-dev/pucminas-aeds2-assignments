/**
 * Código fonte - Implementação da Lista Simples Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Flexible Singly Linked List
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

class List {
    private Cell first, last;

    public List() {
        this.first = new Cell();
        last = first;
    }

    public void insertStart(int value) {
        Cell temp = new Cell(value);

        temp.next = first.next;
        first.next = temp;

        if (first == last) {
            last = temp;
        }

        temp = null;
    }

    public void insertEnd(int value) {
        last.next = new Cell(value);
        last = last.next;
    }

    public void insert(int value, int position) {
        int length = length();

        if (position < 0 || position > length) {
            throw new Error("Não foi possível inserir valor na lista.");
        } else if (position == 0) {
            insertStart(value);
        } else if (position == length) {
            insertEnd(value);
        } else {
            Cell i = first;

            for (int j = 0; j < position; j++, i = i.next)
                ;

            Cell temp = new Cell(value);

            temp.next = i.next;
            i.next = temp;

            temp = i = null;
        }
    }

    public int removeStart() {
        if (first == last) {
            throw new Error("Não foi possível remover um valor da lista.");
        }

        Cell temp = first.next;
        first.next = first.next.next;

        int element = temp.element;

        temp.next = null;
        temp = null;

        return element;
    }

    public int removeEnd() {
        if (first == last) {
            throw new Error("Não foi possível remover um valor da lista.");
        }

        Cell i;

        for (i = first; i.next != last; i = i.next)
            ;

        int element = i.element;

        last = i;
        i = last.next = null;

        return element;
    }

    public int remove(int value, int position) {
        int element, length = length();

        if (position < 0 || position > length) {
            throw new Error("Não foi possível remover um valor da lista.");
        } else if (position == 0) {
            element = removeStart();
        } else if (position == length) {
            element = removeEnd();
        } else {
            Cell i = first;

            for (int j = 0; j < position; j++, i = i.next)
                ;

            Cell temp = i.next;

            element = temp.element;
            i.next = temp.next;

            temp.next = null;
            i = temp = null;
        }

        return element;
    }

    public int length() {
        int length = 0;
        for (Cell i = first; i != last; i = i.next, length++)
            ;
        return length;
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
        List flexibleSimpleList = new List();

        System.out.println("Inserindo 1 no início:");
        flexibleSimpleList.insertStart(1);
        flexibleSimpleList.show();

        System.out.println("\n\nInserindo 2 no final:");
        flexibleSimpleList.insertEnd(2);
        flexibleSimpleList.show();

        System.out.println("\n\nInserindo 0 no início:");
        flexibleSimpleList.insertStart(0);
        flexibleSimpleList.show();

        System.out.println("\n\nInserindo 3 na posição 1:");
        flexibleSimpleList.insert(3, 1);
        flexibleSimpleList.show();

        System.out.println("\n\nInserindo 4 no final:");
        flexibleSimpleList.insertEnd(4);
        flexibleSimpleList.show();

        System.out.println("\n\nRemovendo do início:");
        flexibleSimpleList.removeStart();
        flexibleSimpleList.show();

        System.out.println("\n\nRemovendo do final:");
        flexibleSimpleList.removeEnd();
        flexibleSimpleList.show();

        System.out.println("\n\nRemovendo da posição 1:");
        flexibleSimpleList.remove(3, 1);
        flexibleSimpleList.show();
    }
}