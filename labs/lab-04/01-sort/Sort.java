import java.util.Scanner;

/**
 * LAB04Q01 - Sort sort sort
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 08/09/2024
 */

public class Sort {
    /**
     * Verifica se dois números devem ser trocados de acordo com as regras de ordenação.
     * A comparação é feita com base no módulo de M. Se houver empate no módulo,
     * números ímpares precedem pares. Para números do mesmo tipo, segue a ordem
     * definida para ímpares (decrescente) e pares (crescente).
     *
     * @param a primeiro número a ser comparado
     * @param b segundo número a ser comparado
     * @param M valor utilizado para calcular o módulo dos números
     * @return true se os números devem ser trocados, false caso contrário
     */
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

    /**
     * Verifica se um número é ímpar.
     *
     * @param num número a ser verificado
     * @return true se o número for ímpar, false se for par
     */
    public static boolean isOdd(int num) {
        return num % 2 != 0;
    }

    /**
     * Função principal que processa a entrada e realiza a ordenação dos números
     * com base nas regras fornecidas. A entrada consiste em pares de números N e M,
     * onde N é o número de inteiros a serem ordenados e M é o valor utilizado para
     * calcular o módulo. O programa ordena os números conforme a comparação definida
     * e exibe os resultados.
     */
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