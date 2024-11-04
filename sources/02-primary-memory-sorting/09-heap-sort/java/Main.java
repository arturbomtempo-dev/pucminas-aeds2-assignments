public class Main {
    static int[] numbersArray;
    static int n;

    public static void swap(int i, int j) {
        int temp = numbersArray[i];
        numbersArray[i] = numbersArray[j];
        numbersArray[j] = temp;
    }

    public static int getBiggerSon(int i, int length) {
        int son = 2 * i;

        if (son + 1 < length && numbersArray[son] < numbersArray[son + 1]) {
            son++;
        }

        return son < length ? son : -1;
    }

    public static boolean hasSon(int i, int length) {
        return (2 * i < length);
    }

    public static void buildHeap(int length) {
        for (int i = length / 2; i >= 1; i--) {
            rebuildHeap(i, length);
        }
    }

    public static void rebuildHeap(int i, int length) {
        while (hasSon(i, length)) {
            int son = getBiggerSon(i, length);

            if (son != -1 && numbersArray[i] < numbersArray[son]) {
                swap(i, son);
                i = son;
            } else {
                i = length;
            }
        }
    }

    public static void heapSort() {
        buildHeap(n);

        int length = n - 1;

        while (length > 0) {
            swap(1, length--);
            rebuildHeap(1, length + 1);
        }
    }

    public static void main(String[] args) {
        numbersArray = new int[]{ 0, 12, 4, 8, 2, 14, 17, 6, 18, 10, 16, 15, 5, 13, 9, 1, 11, 7, 3 };
        n = numbersArray.length;

        System.out.println("Array original:");

        for (int i = 1; i < n; i++) {
            System.out.print(numbersArray[i] + " ");
        }
        
        System.out.println();

        heapSort();

        System.out.println("Array ordenado:");

        for (int i = 1; i < n; i++) {
            System.out.print(numbersArray[i] + " ");
        }

        System.out.println();
    }
}