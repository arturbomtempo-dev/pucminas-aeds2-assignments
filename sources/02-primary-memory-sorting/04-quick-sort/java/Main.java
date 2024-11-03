public class Main {
    public static void swap(int[] numbersArray, int i, int j) {
        int temp = numbersArray[i];
        numbersArray[i] = numbersArray[j];
        numbersArray[j] = temp; 
    }

    public static void quickSort(int[] numbersArray, int left, int right) {
        int i = left, j = right;
        int pivot = numbersArray[(left + right) / 2];

        while (i <= j) {
            while (numbersArray[i] < pivot) {
                i++;               
            }

            while (numbersArray[j] > pivot) {
                j--;                
            }

            if (i <= j) {
                swap(numbersArray, i, j);
                i++;
                j--;
            }
        }

        if (left < j) {
            quickSort(numbersArray, left, j);
        }

        if (i < right) {
            quickSort(numbersArray, i, right);
        }
    }

    public static void main(String[] args) {
        int[] numbers = { 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };

        System.out.println("Array original:");

        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }

        System.out.println();

        quickSort(numbers, 0, numbers.length - 1);

        System.out.println("Array ordenado:");

        for (int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }
    }
}