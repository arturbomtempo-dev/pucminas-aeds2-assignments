import java.util.Scanner;

/**
 * TP01Q01 - Palindromo
 * 
 * @author Artur Bomtempo Colen
 * @version 1 26/08
 */

public class Palindrome {
    /**
     * Verifica se uma palavra é um palíndromo.
     * 
     * @param word A palavra a ser verificada.
     * @return {@code true} se a palavra for um palíndromo, {@code false} caso contrário.
     */
    public static boolean verifyPalindrome(String word) {
        boolean isPalindrome = true;

        for (int i = 0; i < word.length() / 2; i++) {
            if (word.charAt(i) != word.charAt(word.length() - 1 - i)) {
                isPalindrome = false;
            }
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

            if (!isEnd(word)) {
                boolean wordIsPalindrome = verifyPalindrome(word);

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