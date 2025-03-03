import java.util.Scanner;

/**
 * LAB01Q02 - Aquecimento Recursivo
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/08/2024
 */

public class Main {
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