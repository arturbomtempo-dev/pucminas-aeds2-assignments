/**
 * Código fonte - Implementação de Pilha
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Stack
 * @language Java
 * @version 1.0
 */

class Stack {
    private static final int LENGTH = 6;
    private int[] array = new int[LENGTH];
    private int n = 0;

    public void start() {
        this.n = 0;
    }

    public void push(int value) {
        if (n >= LENGTH) {
            System.out.println("Erro ao inserir dado na pilha.");
            System.exit(1);
        }

        array[n] = value;
        n++;
    }

    public int pop() {
        if (n == 0) {
            System.out.println("Erro ao remover dado da pilha.");
            System.exit(1);
        }

        return array[--n];
    }

    public int peek() {
        if (n == 0) {
            System.out.println("Pilha vazia.");
            System.exit(1);
        }

        return array[n - 1];
    }

    public void show() {
        System.out.print("[");

        for (int i = 0; i < n; i++) {
            System.out.print(array[i]);

            if (i < n - 1) {
                System.out.print(", ");
            }
        }

        System.out.println("]");
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("===== Pilha =====");

        Stack stack = new Stack();

        stack.start();

        stack.push(1);
        stack.push(7);
        stack.push(9);
        stack.push(3);
        stack.push(8);
        stack.push(4);

        stack.show();

        int x1 = stack.pop();
        int x2 = stack.pop();
        int x3 = stack.pop();

        System.out.println(x1 + ", " + x2 + ", " + x3);

        stack.show();
    }
}