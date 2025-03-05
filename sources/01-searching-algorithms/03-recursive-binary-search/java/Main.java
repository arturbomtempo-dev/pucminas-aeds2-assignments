import java.util.Arrays;
import java.util.Random;

/**
 * Código fonte - Implementação de Pesquisa Binária Recursiva
 *
 * @author Artur Bomtempo Colen
 * @algorithm Recursive Binary Search
 * @type Search Algorithm
 * @language Java
 * @version 1.0
 */

public class Main {
    public static int binarySearch(int[] arr, int left, int right, int target) {
        if (left > right) {
            return -1;
        }

        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] < target) {
            return binarySearch(arr, mid + 1, right, target);
        } else {
            return binarySearch(arr, left, mid - 1, target);
        }
    }

    public static void generateRandomArray(int[] arr) {
        Random rand = new Random();

        for (int i = 0; i < arr.length; i++) {
            arr[i] = rand.nextInt(100) + 1;
        }
    }

    public static void printArray(int[] arr) {
        System.out.print("[ ");

        for (int num : arr) {
            System.out.print(num + " ");
        }

        System.out.println("]");
    }

    public static void main(String[] args) {
        int[] arr = new int[10];
        generateRandomArray(arr);
        Arrays.sort(arr);
        printArray(arr);

        int[] targets = { 30, 50, 75, 15 };

        for (int target : targets) {
            System.out.println("\nProcurando pelo valor " + target + "...");
            int result = binarySearch(arr, 0, arr.length - 1, target);

            if (result != -1) {
                System.out.println("Valor " + target + " encontrado no índice " + result + ".");
            } else {
                System.out.println("Valor " + target + " não encontrado no vetor.");
            }
        }
    }
}