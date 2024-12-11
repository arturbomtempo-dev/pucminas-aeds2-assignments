import java.util.Scanner;

/**
 * BEE 2929
 * 
 * @author Artur Bomtempo Colen
 * @version 2.0, 05/11/2024
 */

class Stack {
    int[] array;
    int n;

    public Stack() {
        array = new int[6];
        n = 0;
    }

    public Stack(int value) {
        array = new int[value];
    }

    public void push(int value) {
        if (n >= array.length) {
            throw new Error("Não foi possível inserir um valor na pilha.");
        }

        array[n] = value;
        n++;
    }

    public int pop() {
        if (n == 0) {
            throw new Error("Não foi possível remover um valor da pilha.");
        }

        return array[--n];
    }

    public int searchSmaller() {
        int smaller = array[0];

        for (int i = 1; i < n; i++) {
            if (smaller > array[i]) {
                smaller = array[i];
            }
        }

        return smaller;
     }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();
        sc.nextLine();

        Stack presentsStack = new Stack(N);

        for (int i = 0; i < N; i++) {
            String operation = sc.next();

            if (operation.equals("PUSH")) {
                int value = sc.nextInt();
                sc.nextLine();

                presentsStack.push(value);
            } else if (operation.equals("POP")) {
                presentsStack.pop();
            } else if (operation.equals("MIN")) {
                int smaller = presentsStack.searchSmaller();
                System.out.println(smaller);
            }
        }

        sc.close();
    }
}