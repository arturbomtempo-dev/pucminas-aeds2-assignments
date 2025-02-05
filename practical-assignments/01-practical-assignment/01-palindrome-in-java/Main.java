import java.util.Scanner;

/**
 * TP01Q01 - Palindromo
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 26/08/2024
 */

public class Main {
    public static boolean verifyPalindrome(String word) {
        boolean isPalindrome = true;

        for (int i = 0; i < word.length() / 2; i++) {
            if (word.charAt(i) != word.charAt(word.length() - 1 - i)) {
                isPalindrome = false;
            }
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