import java.util.Random;

/**
 * LAB06 - Quicksort e seu pivô
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 07/10/2024
 */

public class Main {
    public static void swap(int i, int j, int[] array) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public static void QuickSortFirstPivot(int[] array, int left, int right) {
        if (left < right) {
            int pivotIndex = partitionFirstPivot(array, left, right);
            QuickSortFirstPivot(array, left, pivotIndex - 1);
            QuickSortFirstPivot(array, pivotIndex + 1, right);
        }
    }
    
    private static int partitionFirstPivot(int[] array, int left, int right) {
        int pivot = array[left];
        int i = left + 1;

        for (int j = left + 1; j <= right; j++) {
            if (array[j] < pivot) {
                swap(i, j, array);
                i++;
            }
        }
        swap(left, i - 1, array);
        return i - 1;
    }
    
    public static void QuickSortLastPivot(int[] array, int left, int right) {
        if (left < right) {
            int pivotIndex = partitionLastPivot(array, left, right);
            QuickSortLastPivot(array, left, pivotIndex - 1);
            QuickSortLastPivot(array, pivotIndex + 1, right);
        }
    }
    
    private static int partitionLastPivot(int[] array, int left, int right) {
        int pivot = array[right];
        int i = left;

        for (int j = left; j < right; j++) {
            if (array[j] < pivot) {
                swap(i, j, array);
                i++;
            }
        }
        swap(i, right, array);
        return i;
    }
    
    public static void QuickSortRandomPivot(int[] array, int left, int right) {
        if (left < right) {
            int pivotIndex = partitionRandomPivot(array, left, right);
            QuickSortRandomPivot(array, left, pivotIndex - 1);
            QuickSortRandomPivot(array, pivotIndex + 1, right);
        }
    }
    
    private static int partitionRandomPivot(int[] array, int left, int right) {
        Random rand = new Random();
        int pivotIndex = left + rand.nextInt(right - left + 1);
        swap(pivotIndex, right, array);
        return partitionLastPivot(array, left, right);
    }
    
    public static void QuickSortMedianOfThree(int[] array, int left, int right) {
        if (left < right) {
            int pivotIndex = partitionMedianOfThree(array, left, right);
            QuickSortMedianOfThree(array, left, pivotIndex - 1);
            QuickSortMedianOfThree(array, pivotIndex + 1, right);
        }
    }
    
    private static int partitionMedianOfThree(int[] array, int left, int right) {
        int mid = (left + right) / 2;
        int pivot = medianOfThree(array, left, mid, right);
        swap(pivot, right, array);
        return partitionLastPivot(array, left, right);
    }
    
    private static int medianOfThree(int[] array, int a, int b, int c) {
        if (array[a] > array[b]) {
            swap(a, b, array);
        }
        if (array[b] > array[c]) {
            swap(b, c, array);
        }
        if (array[a] > array[b]) {
            swap(a, b, array);
        }
        return b;
    }
    
    public static void main(String[] args) {
        int[] sizes = { 100, 1000, 10000 };
        Random rand = new Random();

        for (int size : sizes) {
            int[] arrayOrdered = new int[size];
            int[] arrayRandom = new int[size];
            int[] arrayAlmostSorted = new int[size];

            for (int i = 0; i < size; i++) {
                arrayOrdered[i] = i;
                arrayRandom[i] = rand.nextInt(size);
                arrayAlmostSorted[i] = i;

                if (i % 10 == 0) {
                    arrayAlmostSorted[i] = rand.nextInt(size);
                }
            }

            System.out.println("Testando com array de tamanho: " + size);

            long startTime, endTime;

            int[] arrayTest = arrayOrdered.clone();

            startTime = System.nanoTime();
            QuickSortFirstPivot(arrayTest, 0, arrayTest.length - 1);
            endTime = System.nanoTime();
            System.out.println("Tempo QuickSort (Primeiro Pivô): " + (endTime - startTime) + " ns");

            arrayTest = arrayOrdered.clone();
            startTime = System.nanoTime();
            QuickSortLastPivot(arrayTest, 0, arrayTest.length - 1);
            endTime = System.nanoTime();
            System.out.println("Tempo QuickSort (Último Pivô): " + (endTime - startTime) + " ns");

            arrayTest = arrayOrdered.clone();
            startTime = System.nanoTime();
            QuickSortRandomPivot(arrayTest, 0, arrayTest.length - 1);
            endTime = System.nanoTime();
            System.out.println("Tempo QuickSort (Pivô Aleatório): " + (endTime - startTime) + " ns");

            arrayTest = arrayOrdered.clone();
            startTime = System.nanoTime();
            QuickSortMedianOfThree(arrayTest, 0, arrayTest.length - 1);
            endTime = System.nanoTime();
            System.out.println("Tempo QuickSort (Mediana de Três): " + (endTime - startTime) + " ns");
        }
    }
}