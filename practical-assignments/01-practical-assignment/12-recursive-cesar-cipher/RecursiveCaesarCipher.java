import java.util.Scanner;

/**
 * TP01Q12 - RECURSIVO - Ciframento de César
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 30/08/2024
 */

public class RecursiveCaesarCipher {
    /**
     * Criptografa uma determinada mensagem deslocando cada caractere ASCII
     * imprimível (de 32 a 126) três posições à frente na tabela ASCII.
     *
     * Se o caractere ultrapassar o limite dos imprimíveis, ele volta ao início
     * da faixa imprimível.
     *
     * @param message A mensagem que será criptografada.
     * @param index O índice atual na string que está sendo processado.
     * @return A mensagem criptografada, com cada caractere imprimível deslocado.
     */
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
                String encryptedMessage = encrypt(message, 0);
                System.out.println(encryptedMessage);
            }
        }

        sc.close();
    }
}