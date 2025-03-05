import java.util.Arrays;
import java.util.Random;

/**
 * Código fonte - Implementação de Pesquisa Binária
 *
 * @author Artur Bomtempo Colen
 * @algorithm Binary Search
 * @type Search Algorithm
 * @language Java
 * @version 1.0
 */

public class Main {
    public static int binarySearch(int[] array, int target) {
        int left = 0;
        int right = array.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (array[mid] == target) {
                return mid;
            } else if (array[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
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
        Arrays.sort(array);
        printArray(array);

        int[] searchTargets = { 30, 50, 75, 15 };

        for (int target : searchTargets) {
            System.out.println("\nProcurando pelo valor " + target + "...");
            int result = binarySearch(array, target);

            if (result != -1) {
                System.out.println("Valor " + target + " encontrado no índice " + result + ".");
            } else {
                System.out.println("Valor " + target + " não encontrado no vetor.");
            }
        }
    }
}