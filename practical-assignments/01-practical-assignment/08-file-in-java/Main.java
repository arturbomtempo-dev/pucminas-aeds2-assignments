import java.io.RandomAccessFile;
import java.util.Scanner;
import java.io.File;

/**
 * TP01Q08 - Arquivo em Java
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 31/08/2024
 */

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();

        try {
            File file = new File("values.txt");
            RandomAccessFile raf = new RandomAccessFile(file, "rw");

            for (int i = 0; i < n; i++) {
                double value = scanner.nextDouble();
                raf.writeDouble(value);
            }

            raf.close();

            raf = new RandomAccessFile(file, "r");
            long filePointer = raf.length() - 8;

            while (filePointer >= 0) {
                raf.seek(filePointer);
                double value = raf.readDouble();

                if (value == Math.floor(value)) {
                    System.out.println((int) value);
                } else {
                    System.out.println(value);
                }

                filePointer -= 8;
            }

            raf.close();

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            scanner.close();
        }
    }
}