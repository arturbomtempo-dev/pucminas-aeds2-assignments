public class Main {
    public static void insertionSort(int[] numbersArray) {
        int n = numbersArray.length;

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
        int[] numbers = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };

        System.out.println("Array original:");

        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }

        System.out.println();

        insertionSort(numbers);

        System.out.println("Array ordenado:");

        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }
    }
}