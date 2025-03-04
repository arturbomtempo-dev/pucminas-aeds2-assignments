/**
 * Código fonte - Implementação da Tabela Hash Indireta com Lista Simples Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Hash Table with Indirect Addressing and Flexible Linked List
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

    public boolean removeByValue(int value) {
        boolean removed = false;

        Cell prev = first;

        for (Cell i = first.next; i != null; prev = i, i = i.next) {
            if (i.element == value) {
                prev.next = i.next;

                if (i == last) {
                    last = prev;
                }

                i.next = null;
                removed = true;
                break;
            }
        }

        return removed;
    }

    public int length() {
        int length = 0;
        for (Cell i = first; i != last; i = i.next, length++)
            ;
        return length;
    }

    public boolean search(int value) {
        boolean found = false;

        for (Cell i = first.next; i != null; i = i.next) {
            if (i.element == value) {
                found = true;
                i = last;
            }
        }

        return found;
    }

    public void show() {
        System.out.print("[");

        for (Cell i = first.next; i != null; i = i.next) {
            System.out.print(i.element + " ");
        }

        System.out.print("]");
    }
}

class Hash {
    List table[];
    int size;

    public Hash() {
        this.size = 7;
    }

    public Hash(int size) {
        this.size = size;
        this.table = new List[size];

        for (int i = 0; i < size; i++) {
            table[i] = new List();
        }
    }

    public int h(int value) {
        return value % size;
    }

    public void inserStart(int value) {
        int i = h(value);
        table[i].insertStart(value);
    }

    public boolean search(int value) {
        int i = h(value);
        return table[i].search(value);
    }

    public boolean removal(int value) {
        int i = h(value);
        boolean removed = table[i].removeByValue(value);

        return removed;
    }
}

public class Main {
    public static void main(String[] args) {
        Hash hashTable = new Hash(7);

        System.out.println("Inserindo valores...");
        hashTable.inserStart(10);
        hashTable.inserStart(23);
        hashTable.inserStart(36);
        hashTable.inserStart(49);
        hashTable.inserStart(15);
        hashTable.inserStart(64);

        System.out.println("\nTabela Hash após inserções:");
        for (int i = 0; i < 7; i++) {
            System.out.print("Índice " + i + ": ");
            hashTable.table[i].show();
            System.out.println();
        }

        System.out.println("\nPesquisando valores...");
        System.out.println("Valor 23 encontrado? " + hashTable.search(23));
        System.out.println("Valor 99 encontrado? " + hashTable.search(99));

        System.out.println("\nRemovendo valores...");
        System.out.println("Valor 23 removido? " + hashTable.removal(23));
        System.out.println("Valor 99 removido? " + hashTable.removal(99));

        System.out.println("\nTabela Hash após remoções:");
        for (int i = 0; i < 7; i++) {
            System.out.print("Índice " + i + ": ");
            hashTable.table[i].show();
            System.out.println();
        }
    }
}