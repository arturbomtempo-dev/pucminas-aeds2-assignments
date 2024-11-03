public class Main {
    public static void swap(int[] numbersArray, int i, int j) {
        int temp = numbersArray[i];
        numbersArray[i] = numbersArray[j];
        numbersArray[j] = temp;
    }

    public static void selectionSort(int[] numbersArray) {
        int n = numbersArray.length;

        for (int i = 0; i < n - 1; i++) {
            int smallest = i;

            for (int j = i + 1; j < n; j++) {
                if (numbersArray[smallest] > numbersArray[j]) {
                    smallest = j;
                }
            }

            swap(numbersArray, smallest, i);
        }
    }

    public static void main(String[] args) {
        int[] numbers = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };

        System.out.println("Array original:");

        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }

        System.out.println();

        selectionSort(numbers);

        System.out.println("Array ordenado:");

        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }
    }
}