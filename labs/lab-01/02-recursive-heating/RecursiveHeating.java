import java.util.Scanner;

/**
 * LAB01Q02 - Aquecimento Recursivo
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/08/2024
 */

public class RecursiveHeating {
    /**
     * Conta o número de letras maiúsculas de forma recursiva.
     *
     * @param word  a string de entrada a ser verificada.
     * @param index o índice atual que está sendo verificado.
     * @return o número de letras maiúsculas encontradas até o momento.
     */
    private static int checkCapitalLetters(String word, int index) {
        int count = 0;

        if (index < word.length()) {
            char currentChar = word.charAt(index);

            if (currentChar >= 'A' && currentChar <= 'Z') {
                count = 1;
            }
            
            count += checkCapitalLetters(word, index + 1);
        }

        return count;
    }

    /**
     * Método principal que lê strings de entrada do usuário, conta o número de
     * letras maiúsculas em cada string de forma recursiva e imprime o resultado.
     * O programa é finalizado quando o usuário insere a palavra "FIM".
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String input;

        while (!(input = sc.nextLine()).equals("FIM")) {
            int numCapitalLetters = checkCapitalLetters(input, 0);
            System.out.println(numCapitalLetters);
        }

        sc.close();
    }
}