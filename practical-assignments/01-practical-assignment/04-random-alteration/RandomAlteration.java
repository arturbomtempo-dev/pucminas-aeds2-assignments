import java.util.Random;
import java.util.Scanner;

/**
 * TP01Q04 - Alteração Aleatória
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 27/08/2024
 */

public class RandomAlteration {
    /**
     * Substitui todas as ocorrências de uma letra minúscula selecionada aleatoriamente 
     * na string de entrada por outra letra minúscula selecionada aleatoriamente. O método 
     * gera duas letras minúsculas aleatórias e substitui todas as ocorrências da primeira 
     * letra pela segunda na string de entrada fornecida.
     *
     * @param input A mensagem em que a substituição de letras ocorrerá
     * @param generator O objeto Random usado para gerar letras aleatórias
     * @return uma nova string com as substituições especificadas aplicadas
     */
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
     * Método principal que lê as linhas de entrada, verifica se a linha lida 
     * não é "FIM", e então substitui letras aleatórias na linha por outras letras 
     * aleatórias antes de exibir a linha alterada na saída padrão.
     */
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