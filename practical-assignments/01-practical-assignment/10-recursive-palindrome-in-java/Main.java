import java.util.Scanner;

/**
 * TP01Q10 - RECURSIVO - Palíndromo
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 28/08/2024
 */

public class Main {
    public static boolean verifyPalindrome(String word, int left, int right) {
        boolean isPalindrome = true;

        if (word.charAt(left) != word.charAt(right)) {
            isPalindrome = false;
        } else if (left < right) {
            isPalindrome = verifyPalindrome(word, left + 1, right - 1);
        }

        return isPalindrome;
    }

    public static boolean isEnd(String input) {
        return input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M';
    }

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