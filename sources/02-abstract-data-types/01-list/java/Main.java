/**
 * Código fonte - Implementação de Lista
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type List
 * @language Java
 * @version 1.0
 */

class List {
    private int[] array;
    private int n;

    public List() {
        this.array = new int[6];
        this.n = 0;
    }

    public List(int length) {
        this.array = new int[length];
        this.n = 0;
    }

    public void insertStart(int value) {
        if (n >= array.length) {
            throw new Error("Erro ao inserir dado na lista.");
        }

        for (int i = n; i > 0; i--) {
            array[i] = array[i - 1];
        }

        array[0] = value;
        n++;
    }

    public void insertEnd(int value) {
        if (n >= array.length) {
            throw new Error("Erro ao inserir dado na lista.");
        }

        array[n] = value;
        n++;
    }

    public void insert(int value, int position) {
        if (n >= array.length || position < 0 || position > n) {
            throw new Error("Erro ao inserir dado na lista.");
        }

        for (int i = n; i > position; i--) {
            array[i] = array[i - 1];
        }

        array[position] = value;
        n++;
    }

    public int removeStart() {
        if (n == 0) {
            throw new Error("Erro ao remover dado da lista.");
        }

        int valueRemoved = array[0];
        n--;

        for (int i = 0; i < n; i++) {
            array[i] = array[i + 1];
        }

        return valueRemoved;
    }

    public int removeEnd() {
        if (n == 0) {
            throw new Error("Erro ao remover dado da lista.");
        }

        return array[--n];
    }

    public int remove(int position) {
        if (n == 0 || position < 0 || position > n) {
            throw new Error("Erro ao remover dado da lista.");
        }

        int valueRemoved = array[position];
        n--;

        for (int i = position; i < n; i++) {
            array[i] = array[i + 1];
        }

        return valueRemoved;
    }

    public void show() {
        System.out.print("[");

        for (int i = 0; i < n; i++) {
            System.out.print(array[i] + ", ");
        }

        System.out.print("]");
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("===== Lista Linear =====");

        List list = new List(6);
        int x1, x2, x3;

        list.insertStart(1);
        list.insertEnd(7);
        list.insertEnd(9);
        list.insertStart(3);
        list.insert(8, 3);
        list.insert(4, 2);

        list.show();

        x1 = list.removeStart();
        x2 = list.removeEnd();
        x3 = list.remove(2);

        System.out.println();
        System.out.println(x1 + ", " + x2 + ", " + x3);

        list.show();
    }
}