/**
 * Código fonte - Implementação da Lista Dupla Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Flexible Doubly Linked List
 * @language Java
 * @version 1.0
 */

class DoubleCell {
    public int element;
    public DoubleCell next, previous;

    public DoubleCell() {
        this.element = 0;
        this.next = this.previous = null;
    }

    public DoubleCell(int value) {
        this.element = value;
        this.next = this.previous = null;
    }
}

class DoubleList {
    private DoubleCell first, last;

    public DoubleList() {
        this.first = new DoubleCell();
        last = first;
    }

    public void insertStart(int value) {
        DoubleCell temp = new DoubleCell(value);

        temp.previous = first;
        temp.next = first.next;
        first.next = temp;

        if (first == last) {
            last = temp;
        } else {
            temp.next.previous = temp;
        }

        temp = null;
    }

    public void insertEnd(int value) {
        last.next = new DoubleCell(value);
        last.next.previous = last;
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
            DoubleCell i = first;

            for (int j = 0; j < position; j++, i = i.next)
                ;

            DoubleCell temp = new DoubleCell(value);

            temp.previous = i;
            temp.next = i.next;
            temp.previous.next = temp.next.previous = temp;

            temp = i = null;
        }
    }

    public int removeStart() {
        if (first == last) {
            throw new Error("Não foi possível remover um valor da lista.");
        }

        DoubleCell temp = first.next;
        first.next = first.next.next;

        int element = temp.element;

        temp.next = first.previous = null;
        temp = null;

        return element;
    }

    public int removeEnd() {
        if (first == last) {
            throw new Error("Não foi possível remover um valor da lista.");
        }

        int element = last.element;

        last = last.previous;
        last.next.previous = null;
        last.next = null;

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
            DoubleCell i = first.next;

            for (int j = 0; j < position; j++, i = i.next)
                ;

            i.previous.next = i.next;
            i.next.previous = i.previous;

            element = i.element;

            i.next = i.previous = null;
            i = null;
        }

        return element;
    }

    public int length() {
        int length = 0;
        for (DoubleCell i = first; i != last; i = i.next, length++)
            ;
        return length;
    }

    public void show() {
        System.out.print("[");

        for (DoubleCell i = first.next; i != null; i = i.next) {
            System.out.print(i.element + " ");
        }

        System.out.print("]");
    }
}

public class Main {
    public static void main(String[] args) {
        DoubleList flexibleSimpleList = new DoubleList();

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