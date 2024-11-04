public class Main {
    static int[] numbersArray;
    static int n;

    public static void swap(int i, int j) {
        int temp = numbersArray[i];
        numbersArray[i] = numbersArray[j];
        numbersArray[j] = temp;
    }

    public static void quickSort(int left, int right) {
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
                swap(i, j);
                i++;
                j--;
            }
        }

        if (left < j) {
            quickSort(left, j);
        }

        if (i < right) {
            quickSort(i, right);
        }
    }

    public static void main(String[] args) {
        numbersArray = new int[]{ 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
        n = numbersArray.length;

        System.out.println("Array original:");

        for (int i = 0; i < n; i++) {
            System.out.print(numbersArray[i] + " ");
        }

        System.out.println();

        quickSort(0, n - 1);

        System.out.println("Array ordenado:");

        for (int i = 0; i < n; i++) {
            System.out.print(numbersArray[i] + " ");
        }
    }
}