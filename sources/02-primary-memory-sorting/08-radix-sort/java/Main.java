public class Main {
    static int[] numbersArray;
    static int n;

    public static int getBiggestNumber() {
        int biggest = numbersArray[0];

        for (int i = 1; i < n; i++) {
            if (numbersArray[i] > biggest) {
                biggest = numbersArray[i];
            }
        }

        return biggest;
    }

    public static int[] countingSort(int exp) {
        int[] count = new int[10];
        int[] sorted = new int[n];

        for (int i = 0; i < count.length; i++) {
            count[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            count[(numbersArray[i] / exp) % 10]++;
        }

        for (int i = 1; i < count.length; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            sorted[count[(numbersArray[i] / exp) % 10] - 1] = numbersArray[i];
            count[(numbersArray[i] / exp) % 10]--;
        }

        return sorted;
    }

    public static void radixSort() {
        int max = getBiggestNumber();

        for (int exp = 1; max / exp > 0; exp *= 10) {
            numbersArray = countingSort(exp);
        }
    }

    public static void main(String[] args) {
        numbersArray = new int[]{ 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
        n = numbersArray.length;

        System.out.println("Array original:");

        for (int i = 0; i < numbersArray.length; i++) {
            System.out.print(numbersArray[i] + " ");
        }
        
        System.out.println();

        radixSort();

        System.out.println("Array ordenado:");

        for (int i = 0; i < numbersArray.length; i++) {
            System.out.print(numbersArray[i] + " ");
        }
        
        System.out.println();
    }
}