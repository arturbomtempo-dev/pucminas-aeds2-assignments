import java.util.*;

public class Main {
    private static void bubbleSort(String[] array, int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (array[j].compareTo(array[j + 1]) > 0) {
                    String temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String start = sc.nextLine();

            if (start.equals("1")) {
                String[] packages = new String[10];
                int count = 0; 

                while (sc.hasNextLine()) {
                    String line = sc.nextLine();

                    if (line.equals("0")) {
                        break;
                    }

                    packages[count++] = line;
                }

                bubbleSort(packages, count);

                for (int i = 0; i < count; i++) {
                    System.out.println(packages[i]);
                }

                System.out.println();
            }
        }

        sc.close();
    }
}