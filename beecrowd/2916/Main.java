import java.util.*;

public class Main {
    public static void bubbleSort(int[] numbers, int N) {
        for (int i = 0; i < N - 1; i++) {
            for (int j = 0; j < N - i - 1; j++) {
                if (numbers[j] > numbers[j + 1]) {
                    int temp = numbers[j];
                    numbers[j] = numbers[j + 1];
                    numbers[j + 1] = temp;
                }
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            int N = sc.nextInt();
            int K = sc.nextInt();
            int count = 0;

            int[] numbers = new int[N];

            for (int i = 0; i < N; i++) {
                numbers[i] = sc.nextInt();
            }

            bubbleSort(numbers, N);

            for (int m = N - 1; m > N - 1 - K; m--) {
                count += numbers[m];
            }

            System.out.println(count);
        }

        sc.close();
    }
}