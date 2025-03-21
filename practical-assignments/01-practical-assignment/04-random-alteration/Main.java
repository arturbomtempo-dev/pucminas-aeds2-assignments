import java.util.Random;
import java.util.Scanner;

/**
 * TP01Q04 - Alteração Aleatória
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 27/08/2024
 */

public class Main {
    public static String replaceRandomLetters(String input, Random generator) {
        char firstChar = (char) ('a' + (Math.abs(generator.nextInt()) % 26));
        char secondChar = (char) ('a' + (Math.abs(generator.nextInt()) % 26));

        String result = "";

        for (int i = 0; i < input.length(); i++) {
            char currentChar = input.charAt(i);

            if (currentChar == firstChar) {
                result += secondChar;
            } else {
                result += currentChar;
            }
        }

        return result;
    }

    public static boolean isEnd(String input) {
        return input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M';
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Random generator = new Random();
        generator.setSeed(4);

        while (sc.hasNextLine()) {
            String message = sc.nextLine();

            if (!isEnd(message)) {
                String output = replaceRandomLetters(message, generator);
                System.out.println(output);
            }
        }

        sc.close();
    }
}