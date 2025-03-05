import java.util.Random;

/**
 * Código fonte - Implementação de Pesquisa Sequencial
 *
 * @author Artur Bomtempo Colen
 * @algorithm Sequential Search
 * @type Search Algorithm
 * @language Java
 * @version 1.0
 */

public class Main {
    public static int sequentialSearch(int[] array, int target) {
        for (int i = 0; i < array.length; i++) {
            if (array[i] == target) {
                return i;
            }
        }

        return -1;
    }

    public static void generateRandomArray(int[] array) {
        Random rand = new Random();

        for (int i = 0; i < array.length; i++) {
            array[i] = rand.nextInt(100) + 1;
        }
    }

    public static void printArray(int[] array) {
        System.out.print("[ ");

        for (int num : array) {
            System.out.print(num + " ");
        }

        System.out.println("]");
    }

    public static void main(String[] args) {
        int[] array = new int[10];
        generateRandomArray(array);
        printArray(array);

        int[] searchTargets = { 30, 50, 75, 15 };

        for (int target : searchTargets) {
            System.out.println("\nProcurando pelo valor " + target + "...");
            int result = sequentialSearch(array, target);

            if (result != -1) {
                System.out.println("Valor " + target + " encontrado no índice " + result + ".");
            } else {
                System.out.println("Valor " + target + " não encontrado no vetor.");
            }
        }
    }
}