/**
 * Código fonte - Implementação do Método de Inserção
 *
 * @author Artur Bomtempo Colen
 * @algorithm Sorting
 * @type Insertion Sort
 * @language Java
 * @version 1.0
 */

public class Main {
    static int[] numbersArray;
    static int n;

    public static void insertionSort() {
        for (int i = 1; i < n; i++) {
            int temp = numbersArray[i];
            int j = i - 1;

            while ((j >= 0) && (numbersArray[j] > temp)) {
                numbersArray[j + 1] = numbersArray[j];
                j--;
            }

            numbersArray[j + 1] = temp;
        }
    }

    public static void main(String[] args) {
        numbersArray = new int[] { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
        n = numbersArray.length;

        System.out.println("Array original:");

        for (int i = 0; i < n; i++) {
            System.out.print(numbersArray[i] + " ");
        }

        System.out.println();

        insertionSort();

        System.out.println("Array ordenado:");

        for (int i = 0; i < n; i++) {
            System.out.print(numbersArray[i] + " ");
        }
    }
}