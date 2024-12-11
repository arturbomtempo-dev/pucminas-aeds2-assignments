import java.util.Scanner;

/**
 * BEE 2384
 * 
 * @author Artur Bomtempo Colen
 * @version 2.0, 18/09/2024
 */

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int K, N, countCharsDiff = 0;

        K = sc.nextInt();
        N = sc.nextInt();

        char[] alienAlphabet = new char[K];
        char[] expression = new char[N];

        String alienChars = sc.next();

        for (int i = 0; i < K; i++) {
            alienAlphabet[i] = alienChars.charAt(i);
        }

        String expr = sc.next();

        for (int j = 0; j < N; j++) {
            expression[j] = expr.charAt(j);
        }

        for (int i = 0; i < N; i++) {
            char currentChar = expression[i];
            boolean foundInAlphabet = false;

            for (int j = 0; j < K; j++) {
                if (currentChar == alienAlphabet[j]) {
                    foundInAlphabet = true;
                }
            }

            if (!foundInAlphabet) {
                countCharsDiff++;
            }
        }

        if (countCharsDiff == 0) {
            System.out.println("S");
        } else {
            System.out.println("N");
        }

        sc.close();
    }
}