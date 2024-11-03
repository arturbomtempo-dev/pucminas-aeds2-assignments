public class Main {
    public static void bubbleSort(int[] numbersArray) {
        boolean swapOccurred = true;
        int n = numbersArray.length;

        for (int rep = 0; rep < n - 1 && swapOccurred; rep++) {
            swapOccurred = false;

            for (int b = 0; b < n - (rep + 1); b++) {
                if (numbersArray[b] > numbersArray[b + 1]) {
                    int temp = numbersArray[b];
                    numbersArray[b] = numbersArray[b + 1];
                    numbersArray[b + 1] = temp;
                    swapOccurred = true;
                }
            }
        }
    }

    public static void main(String[] args) {
        int[] numbers = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };

        System.out.println("Array original:");

        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }

        System.out.println();

        bubbleSort(numbers);

        System.out.println("Array ordenado:");

        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }
    }
}