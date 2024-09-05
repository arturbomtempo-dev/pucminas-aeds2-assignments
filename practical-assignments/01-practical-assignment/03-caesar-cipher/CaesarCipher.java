import java.util.Scanner;

/**
 * TP01Q03 - Ciframento de César
 * 
 * @author Artur Bomtempo Colen
 * @version 1 27/08
 */

public class CaesarCipher {
    /**
     * Criptografa uma determinada mensagem deslocando cada caractere ASCII
     * imprimível (de 32 a 126) três posições à frente na tabela ASCII. 
     * 
     * Se o caractere ultrapassar o limite dos imprimíveis, ele volta ao início.
     * 
     * Os caracteres não imprimíveis continuam da forma que estão.
     *
     * @param message A mensagem que será criptografada.
     * @return A mensagem criptografada, com cada caractere imprimível deslocado.
     */
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
     * Método principal que lê as mensagens de entrada, verifica se o que foi digitado é
     * diferente de "FIM" e retorna a mensagem criptografada.
     */
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