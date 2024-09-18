import java.util.Scanner;

/**
 * BEE 2929
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 17/09/2024
 */

public class SmallestStack {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();
        sc.nextLine();

        int[] array = new int[N];
        int top = -1;

        for (int i = 0; i < N; i++) {
            String term = sc.next();

            if (term.equals("PUSH")) {
                int V = sc.nextInt();

                if (top < N - 1) {
                    top++;
                    array[top] = V;
                }
            } else if (term.equals("POP")) {
                if (top >= 0) {
                    top--;
                } else {
                    System.out.println("EMPTY");
                }
            } else if (term.equals("MIN")) {
                if (top >= 0) {
                    int smaller = array[0];
                    
                    for (int j = 1; j <= top; j++) {
                        if (smaller > array[j]) {
                            smaller = array[j];
                        }
                    }

                    System.out.println(smaller);
                } else {
                    System.out.println("EMPTY");
                }
            }
        }

        sc.close();
    }
}