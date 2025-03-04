/**
 * Código fonte - Implementação do Método Shell Sort
 *
 * @author Artur Bomtempo Colen
 * @algorithm Sorting
 * @type Shell Sort
 * @language Java
 * @version 1.0
 */

public class Main {
    static int[] numbersArray;
    static int n;

    public static void colorInsertion(int color, int h) {
        for (int i = (color + h); i < n; i += h) {
            int temp = numbersArray[i];
            int j = i - h;

            while ((j >= 0) && (numbersArray[j] > temp)) {
                numbersArray[j + h] = numbersArray[j];
                j -= h;
            }

            numbersArray[j + h] = temp;
        }
    }

    public static void shellSort() {
        int h = 1;

        do {
            h = (h * 3) + 1;
        } while (h < n);

        do {
            h /= 3;

            for (int color = 0; color < h; color++) {
                colorInsertion(color, h);
            }
        } while (h != 1);
    }

    public static void main(String[] args) {
        numbersArray = new int[] { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
        n = numbersArray.length;

        System.out.println("Array original:");

        for (int i = 0; i < n; i++) {
            System.out.print(numbersArray[i] + " ");
        }

        System.out.println();

        shellSort();

        System.out.println("Array ordenado:");

        for (int i = 0; i < n; i++) {
            System.out.print(numbersArray[i] + " ");
        }
    }
}