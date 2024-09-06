import java.util.Scanner;

/**
 * TP01Q14 - RECURSIVO - Is
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 30/08/2024
 */

public class RecursiveStringChecker {
    /**
     * Esse método verifica de forma recursiva se o dado de entrada é uma vogal.
     *
     * @param input A entrada do usuário.
     * @param index O índice atual na string.
     * @return {@code true} se a entrada for uma vogal, {@code false} caso a entrada não seja uma vogal.
     */
    public static boolean isVowel(String input, int index) {
        boolean vowel = true;

        if (index < input.length()) {
            char c = input.charAt(index);

            if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')) {
                vowel = false;
            } else {
                vowel = isVowel(input, index + 1);
            }
        }

        return vowel;
    }

    /**
     * Esse método verifica de forma recursiva se o dado de entrada é uma consoante.
     *
     * @param input A entrada do usuário.
     * @param index O índice atual na string.
     * @return {@code true} se a entrada for uma consoante, {@code false} caso a entrada não seja uma consoante.
     */
    public static boolean isConsonant(String input, int index) {
        boolean consonant = true;

        if (index < input.length()) {
            char c = input.charAt(index);

            if ((c >= 'a' && c <= 'z' && !isVowel(input, index)) || (c >= 'A' && c <= 'Z' && !isVowel(input, index))) {
                consonant = isConsonant(input, index + 1);
            } else {
                consonant = false;
            }
        }

        return consonant;
    }

    /**
     * Esse método verifica de forma recursiva se o dado de entrada é um número inteiro.
     *
     * @param input A entrada do usuário.
     * @param index O índice atual na string.
     * @return {@code true} se a entrada for um número inteiro, {@code false} caso a entrada não seja um número inteiro.
     */
    public static boolean isInteger(String input, int index) {
        boolean integer = true;

        if (index < input.length()) {
            char c = input.charAt(index);

            if (c < '0' || c > '9') {
                integer = false;
            } else {
                integer = isInteger(input, index + 1);
            }
        }

        return integer;
    }

    /**
     * Esse método verifica de forma recursiva se o dado de entrada é um número real.
     *
     * @param input A entrada do usuário.
     * @param index O índice atual na string.
     * @return {@code true} se a entrada for um número real, {@code false} caso a entrada não seja um número real.
     */
    public static boolean isReal(String input, int index, int dotCount, int commaCount) {
        boolean real = true;

        if (index < input.length()) {
            char c = input.charAt(index);

            if (c >= '0' && c <= '9') {
                real = isReal(input, index + 1, dotCount, commaCount);
            } else if (c == '.') {
                if (dotCount >= 1) {
                    real = false;
                } else {
                    real = isReal(input, index + 1, dotCount + 1, commaCount);
                }
            } else if (c == ',') {
                if (commaCount >= 1) {
                    real = false;
                } else {
                    real = isReal(input, index + 1, dotCount, commaCount + 1);
                }
            } else {
                real = false;
            }
        } else if (input.length() > 0) {
            char lastChar = input.charAt(input.length() - 1);

            if (lastChar == '.' || lastChar == ',') {
                real = false;
            }
        }
        
        return real;
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
     * Método principal que processa a entrada do usuário e realiza uma série de verificações
     * para determinar se cada valor digitado é uma vogal, consoante, número inteiro ou número real.
     * Para cada valor inserido, o programa imprime "SIM" ou "NAO" com base na verificação.
     * O programa continua solicitando entradas até que a palavra "SIM" seja digitada, momento em que
     * ele encerra a execução.
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String input = sc.nextLine();

            if (!isEnd(input)) {
                String result = "";

                if (isVowel(input, 0)) {
                    result += "SIM ";
                } else {
                    result += "NAO ";
                }

                if (isConsonant(input, 0)) {
                    result += "SIM ";
                } else {
                    result += "NAO ";
                }

                if (isInteger(input, 0)) {
                    result += "SIM ";
                } else {
                    result += "NAO ";
                }

                if (isReal(input, 0, 0, 0)) {
                    result += "SIM";
                } else {
                    result += "NAO";
                }

                System.out.println(result);
            }
        }

        sc.close();
    }
}