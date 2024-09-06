import java.util.Scanner;

/**
 * TP01Q10 - RECURSIVO - Palíndromo
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 28/08/2024
 */

public class RecursivePalindrome {
    /**
     * Verifica se uma palavra é um palíndromo de forma recursiva.
     * 
     * Para fazer essa verificação, o método percorre a string verificando se as letras da palavra
     * do início e fim são iguais, caso seja verdade, retorne true. Do contrário, retorna false.
     * 
     * @param word A palavra a ser verificada.
     * @param left O índice inicial da palavra (inicialmente 0).
     * @param O índice final da palavra (inicialmente word.length() - 1).
     * @return {@code true} se o código for um palíndromo, {@code false} se não for um palíndromo.
     */
    public static boolean verifyPalindrome(String word, int left, int right) {
        boolean isPalindrome = true;

        if (word.charAt(left) != word.charAt(right)) {
            isPalindrome = false;
        } else if (left < right) {
            isPalindrome = verifyPalindrome(word, left + 1, right - 1);
        }

        return isPalindrome;
    }

    /**
     * Verifica se a palavra de entrada é "FIM", indicando o término da execução.
     * 
     * @param input A palavra de entrada a ser verificada.
     * @return {@code true} se a palavra for "FIM", {@code false} caso contrário.
     */
    public static boolean isEnd(String input) {
        return input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M';
    }

    /**
     * Método principal que lê palavras da entrada padrão, verifica se são palíndromos,
     * e para a execução quando "FIM" é digitado.
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String word = sc.nextLine();

            if (!isEnd(word) && word.length() > 0) {
                boolean wordIsPalindrome = verifyPalindrome(word, 0, word.length() - 1);

                if (wordIsPalindrome) {
                    System.out.println("SIM");
                } else {
                    System.out.println("NAO");
                }
            }
        }
        
        sc.close();
    }
}