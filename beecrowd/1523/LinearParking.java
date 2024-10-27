import java.util.Scanner;

/**
 * BEE 1523
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 27/10/2024
 */

public class LinearParking {
    /**
     * Verifica se é possível acomodar os carros em um estacionamento
     * baseado nos horários de chegada e saída, considerando a capacidade máxima.
     *
     * @param arrivals   Um array que representa os horários de chegada dos carros.
     * @param departures Um array que representa os horários de saída dos carros.
     * @param N         O número total de carros (tanto chegadas quanto saídas).
     * @param capacity   A capacidade máxima do estacionamento.
     * @return true se todos os carros podem ser acomodados, false caso contrário.
     */
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

    /**
     * Método principal que executa a lógica para verificar se os carros podem ser 
     * acomodados no estacionamento com base nos horários de chegada e saída.
     */
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