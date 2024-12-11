import java.util.Scanner;

/**
 * BEE 1523
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 27/10/2024
 */

public class Main {
    private static boolean checkParking(int[] arrivals, int[] departures, int N, int capacity) {
        int carsInParking = 0;
        int i = 0;
        int j = 0;

        while (i < N) {
            while (j < N && (carsInParking == 0 || departures[j] <= arrivals[i])) {
                carsInParking--;
                j++;
            }

            if (carsInParking < capacity) {
                carsInParking++;
                i++;
            } else {
                return false;
            }
        }

        while (j < N) {
            if (carsInParking > 0) {
                carsInParking--;
                j++;
            } else {
                return false;
            }
        }

        return true;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            int N = sc.nextInt();
            int K = sc.nextInt();

            if (N != 0 && K != 0) {
                int[] arrivals = new int[N];
                int[] departures = new int[N];
                
                for (int i = 0; i < N; i++) {
                    arrivals[i] = sc.nextInt();
                    departures[i] = sc.nextInt();
                }

                boolean result = checkParking(arrivals, departures, N, K);
                System.out.println(result ? "Sim" : "Nao");
            }
        }

        sc.close();
    }
}