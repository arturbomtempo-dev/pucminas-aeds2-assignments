import java.io.RandomAccessFile;
import java.util.Scanner;
import java.io.File;

/**
 * TP01Q08 - Arquivo em Java
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 31/08/2024
 */

public class JavaFile {
    /**
     * Método principal do programa responsável por ler um número 
     * especificado de valores reais, grava-os em um arquivo e, em seguida, 
     * lê o arquivo na ordem inversa, imprimindo os valores sem a parte decimal 
     * se forem inteiros.
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();

        try {
            // Gravação dos valores de entrada em um arquivo
            File file = new File("valores.txt");
            RandomAccessFile raf = new RandomAccessFile(file, "rw");

            for (int i = 0; i < n; i++) {
                double value = scanner.nextDouble();
                raf.writeDouble(value);
            }

            raf.close();

           // Reading the values from the file in reverse order
            raf = new RandomAccessFile(file, "r");
            long filePointer = raf.length() - 8;

            while (filePointer >= 0) {
                raf.seek(filePointer);
                double value = raf.readDouble();

                // Verificar se o valor é um número inteiro e imprimi-lo sem casas decimais
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