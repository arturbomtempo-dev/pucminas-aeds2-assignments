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

class Stack {
    private Cell top;

    public Stack() {
        this.top = null;
    }

    public void insert(int value) {
        Cell temp = new Cell(value);
        temp.next = top;
        top = temp;
        temp = null;
    }

    public int remove() {
        if (top == null) {
            throw new Error("Não foi possível remover um valor da pilha.");
        }

        int element = top.element;
        Cell temp = top;

        top = top.next;
        temp.next = null;
        temp = null;

        return element;
    }

    public void show() {
        System.out.print("[");

        for (Cell i = top; i != null; i = i.next) {
            System.out.print(i.element + " ");
        }

        System.out.print("]");
    }
}

public class Main {
    public static void main(String[] args) {
        Stack flexibleStack = new Stack();

        flexibleStack.insert(3);
        flexibleStack.insert(5);
        flexibleStack.insert(7);

        flexibleStack.show();

        flexibleStack.remove();
        flexibleStack.remove();

        System.out.println();
        flexibleStack.show();
    }
}