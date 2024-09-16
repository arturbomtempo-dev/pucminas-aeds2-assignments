import java.util.Scanner;

/**
 * LAB01Q01 - Aquecimento Iterativo
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/08/2024
 */

public class IterativeHeating {
    /** 
     * Array de letras maiúsculas (A-Z) usado para comparação no método de contagem de letras.
     */
    private static char[] capitalLetters = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

    /**
     * Conta o número de letras maiúsculas na palavra fornecida.
     *
     * @param word a string de entrada a ser verificada quanto a letras maiúsculas.
     * @return o número de letras maiúsculas encontradas na string.
     */
    private static int checkCapitalLetters(String word) {
        int count = 0;

        for (int i = 0; i < word.length(); i++) {
            char currentChar = word.charAt(i);

            for (int j = 0; j < capitalLetters.length; j++) {
                if (currentChar == capitalLetters[j]) {
                    count++;
                }
            }
        }

        return count;
    }

    /**
     * Método principal que lê strings de entrada do usuário, conta o número de
     * letras maiúsculas em cada string e imprime o resultado. O programa é finalizado
     * quando o usuário insere a palavra "FIM".
     *
     * @param args argumentos da linha de comando (não utilizado).
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String input;

        while (!(input = sc.nextLine()).equals("FIM")) {
            int numCapitalLetters = checkCapitalLetters(input);
            System.out.println(numCapitalLetters);
        }

        sc.close();
    }
}