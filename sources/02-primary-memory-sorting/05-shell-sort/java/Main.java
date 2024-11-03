public class Main {
    public static void colorInsertion(int[] numbersArray, int color, int h, int n) {
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

    public static void shellSort(int[] numbersArray) {
        int n = numbersArray.length;
        int h = 1;

        do {
            h = (h * 3) + 1;
        } while (h < n);

        do {
            h /= 3;

            for (int color = 0; color < h; color++) {
                colorInsertion(numbersArray, color, h, n);
            }
        } while (h != 1);
    }

    public static void main(String[] args) {
        int[] numbers = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };

        System.out.println("Array original:");

        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }

        System.out.println();

        shellSort(numbers);

        System.out.println("Array ordenado:");

        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }
    }
}