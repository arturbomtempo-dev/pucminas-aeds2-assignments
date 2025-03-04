/**
 * Código fonte - Implementação do Método Merge Sort
 *
 * @author Artur Bomtempo Colen
 * @algorithm Sorting
 * @type Merge Sort
 * @language Java
 * @version 1.0
 */

public class Main {
    static int[] numbersArray;
    static int n;

    public static void interleave(int left, int middle, int right) {
        int numbersLeft = middle - left + 1;
        int numbersRight = right - middle;

        int[] leftArray = new int[numbersLeft + 1];
        int[] rightArray = new int[numbersRight + 1];

        for (int i = 0; i < numbersLeft; i++) {
            leftArray[i] = numbersArray[left + i];
        }

        for (int j = 0; j < numbersRight; j++) {
            rightArray[j] = numbersArray[middle + 1 + j];
        }

        leftArray[numbersLeft] = Integer.MAX_VALUE;
        rightArray[numbersRight] = Integer.MAX_VALUE;

        int i = 0, j = 0;

        for (int k = left; k <= right; k++) {
            if (leftArray[i] <= rightArray[j]) {
                numbersArray[k] = leftArray[i++];
            } else {
                numbersArray[k] = rightArray[j++];
            }
        }
    }

    public static void mergeSort(int left, int right) {
        if (left < right) {
            int middle = (left + right) / 2;

            mergeSort(left, middle);
            mergeSort(middle + 1, right);
            interleave(left, middle, right);
        }
    }

    public static void main(String[] args) {
        numbersArray = new int[] { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
        n = numbersArray.length;

        System.out.println("Array original:");

        for (int i = 0; i < numbersArray.length; i++) {
            System.out.print(numbersArray[i] + " ");
        }

        System.out.println();

        mergeSort(0, n - 1);

        System.out.println("Array ordenado:");

        for (int i = 0; i < numbersArray.length; i++) {
            System.out.print(numbersArray[i] + " ");
        }

        System.out.println();
    }
}