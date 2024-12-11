import java.util.Scanner;

/**
 * BEE 1088
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 06/11/2024
 */

public class Main {
    static int[] numbersArray;

    public static void swap(int i, int j) {
        int temp = numbersArray[i];
        numbersArray[i] = numbersArray[j];
        numbersArray[j] = temp;
    }

    public static int bubbleSort() {
        int n = numbersArray.length;
        int movements = 0;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (numbersArray[j] > numbersArray[j + 1]) {
                    swap(j, j + 1);
                    movements++;
                }
            }
        }

        return movements;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNext()) {
            int elementsNumber =  sc.nextInt();

            if (elementsNumber != 0) {
                numbersArray = new int[elementsNumber];

                for (int i = 0; i < elementsNumber; i++) {
                    int number = sc.nextInt();

                    numbersArray[i] = number;
                }

                int movements = bubbleSort();

                if (movements % 2 == 0) {
                    System.out.println("Carlos");
                } else {
                    System.out.println("Marcelo");
                }
            }
        }

        sc.close();
    }
}