import java.util.Scanner;

/**
 * TP01Q03 - Ciframento de César
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 27/08/2024
 */

public class Main {
    public static String encrypt(String message) {
        String encryptedMessage = "";

        for (int i = 0; i < message.length(); i++) {
            char currentChar = message.charAt(i);

            if (currentChar >= 32 && currentChar <= 126) {
                char encryptedChar = (char) (currentChar + 3);

                if (encryptedChar > 126) {
                    encryptedChar -= 95;
                }

                encryptedMessage += encryptedChar;
            } else {
                encryptedMessage += currentChar;
            }
        }

        return encryptedMessage;
    }

    public static boolean isEnd(String input) {
        return input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M';
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String message = sc.nextLine();

            if (!isEnd(message)) {
                String encryptedMessage = encrypt(message);
                System.out.println(encryptedMessage);
            }
        }

        sc.close();
    }
}