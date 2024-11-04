public class Main {
    static int[] numbersArray;
    static int n;

    public static void swap(int i, int j) {
        int temp = numbersArray[i];
        numbersArray[i] = numbersArray[j];
        numbersArray[j] = temp;
    }

    public static void selectionSort() {
        for (int i = 0; i < n - 1; i++) {
            int smallest = i;

            for (int j = i + 1; j < n; j++) {
                if (numbersArray[smallest] > numbersArray[j]) {
                    smallest = j;
                }
            }

            swap(smallest, i);
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

        selectionSort();

        System.out.println("Array ordenado:");

        for (int i = 0; i < n; i++) {
            System.out.print(numbersArray[i] + " ");
        }
    }
}