import java.util.Scanner;

/**
 * LAB04Q01 - Sort sort sort
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 08/09/2024
 */

public class Main {
    public static boolean shouldSwap(int a, int b, int M) {
        boolean swap;
        int modA = a % M;
        int modB = b % M;

        if (modA != modB) {
            swap = modA > modB;
        } else if (isOdd(a) && isOdd(b)) {
            swap = a < b;
        } else if (!isOdd(a) && !isOdd(b)) {
            swap = a > b;
        } else {
            swap = !isOdd(a);
        }

        return swap;
    }

    public static boolean isOdd(int num) {
        return num % 2 != 0;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNext()) {
            int N = sc.nextInt();
            int M = sc.nextInt();

            if (!(N == 0 && M == 0)) {
                int[] numbers = new int[N];

                for (int i = 0; i < N; i++) {
                    numbers[i] = sc.nextInt();
                }

                for (int i = 0; i < N - 1; i++) {
                    for (int j = i + 1; j < N; j++) {
                        if (shouldSwap(numbers[i], numbers[j], M)) {
                            int temp = numbers[i];
                            numbers[i] = numbers[j];
                            numbers[j] = temp;
                        }
                    }
                }

                System.out.println(N + " " + M);

                for (int i = 0; i < N; i++) {
                    System.out.println(numbers[i]);
                }

                if (sc.hasNextLine()) {
                    sc.nextLine();
                }
            } else {
                System.out.println("0 0");
                break;
            }
        }

        sc.close();
    }
}