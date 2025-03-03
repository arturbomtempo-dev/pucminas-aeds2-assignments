import java.util.Scanner;

/**
 * LAB05Q01 - Sinuca
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 15/09/2024
 */

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNext()) {
            int N = sc.nextInt();
            int[] array = new int[N];

            for (int i = 0; i < N; i++) {
                array[i] = sc.nextInt();
            }

            while (N > 1) {
                for (int j = 0; j < N - 1; j++) {
                    if (array[j] == array[j + 1]) {
                        array[j] = 1;
                    } else {
                        array[j] = -1;
                    }
                }

                N--;
            }

            if (array[0] == 1) {
                System.out.println("preta");
            } else if (array[0] == -1) {
                System.out.println("branca");
            }
        }

        sc.close();
    }
}