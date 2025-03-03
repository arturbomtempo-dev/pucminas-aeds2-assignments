import java.util.Scanner;

/**
 * LAB01Q01 - Aquecimento Iterativo
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/08/2024
 */

public class Main {
    private static int checkCapitalLetters(String word) {
        int count = 0;

        for (int i = 0; i < word.length(); i++) {
            char currentChar = word.charAt(i);

            if (currentChar >= 65 && currentChar <= 90) {
                count++;
            }
        }

        return count;
    }

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