import java.util.Scanner;

/**
 * LAB02Q02 - Sequencia Espelho
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 25/08/2024
 */

public class MirrorSequence {
    /**
     * O programa lê dois números inteiros (startNumber e endNumber) de um arquivo ou entrada padrão
     * e, em seguida, imprime uma sequência de números de startNumber até endNumber.
     * Após isso, ele inverte a sequência resultante e a adiciona à original para formar um "espelho".
     * O processo continua enquanto houver mais números a serem lidos.
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextInt()) {
            String expression = "";
            int startNumber = sc.nextInt();
            int endNumber = sc.nextInt();

            for (int i = startNumber; i <= endNumber; i++) {
                expression += i;
            }

            for (int j = expression.length() - 1; j >= 0; j--) {
                expression += expression.charAt(j);
            }

            System.out.println(expression);

        }

        sc.close();
    }
}