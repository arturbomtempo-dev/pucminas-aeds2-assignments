import java.util.Scanner;

/**
 * TP01Q12 - RECURSIVO - Ciframento de César
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 30/08/2024
 */

public class Main {
    private static String encrypt(String message, int index) {
        if (index >= message.length()) {
            return "";
        }

        char currentChar = message.charAt(index);
        char encryptedChar;

        if (currentChar >= 32 && currentChar <= 126) {
            encryptedChar = (char) (currentChar + 3);

            if (encryptedChar > 126) {
                encryptedChar -= 95;
            }
        } else {
            encryptedChar = currentChar;
        }

        return encryptedChar + encrypt(message, index + 1);
    }

    public static boolean isEnd(String input) {
        return input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M';
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String message = sc.nextLine();

            if (!isEnd(message)) {
                String encryptedMessage = encrypt(message, 0);
                System.out.println(encryptedMessage);
            }
        }

        sc.close();
    }
}