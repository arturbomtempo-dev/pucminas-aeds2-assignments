import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URI;
import java.net.URL;
import java.util.Scanner;

/**
 * TP01Q07 - Leitura de Página HTML
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 31/08/2024
 */

public class HTMLPageReading {
    /**
     * Realiza uma requisição HTTP a um endereço URL e retorna o conteúdo HTML
     * como uma string.
     * 
     * @param url O endereço da página web a ser acessada.
     * @return O conteúdo HTML da página como uma string.
     */
    private static String httpRequest(String url) {
        URL site;
        InputStream inputstream;
        BufferedReader bufferedReader;
        String response = "";
        String line;

        try {
            site = new URI(url).toURL();
            inputstream = site.openStream();
            bufferedReader = new BufferedReader(new InputStreamReader(inputstream));

            while ((line = bufferedReader.readLine()) != null) {
                response += line + "\n";
            }

            inputstream.close();
        } catch (Exception e) {  }

        return response;
    }

    /**
     * Conta a ocorrência de caracteres específicos em um texto.
     * 
     * @param texto O texto no qual os caracteres serão contados.
     * @param letras Um array de caracteres a serem contados no texto.
     * @return Um array de inteiros representando a contagem de cada caractere em letras.
     */
    private static int[] countLetters(String text, char[] letters) {
        int[] letterCounts = new int[letters.length];

        for (int i = 0; i < text.length(); i++) {
            for (int j = 0; j < letters.length; j++) {
                if (text.charAt(i) == letters[j]) {
                    letterCounts[j]++;
                }
            }
        }

        return letterCounts;
    }

    /**
     * Conta a ocorrência de palavras específicas em um texto.
     * 
     * @param texto   O texto no qual as palavras serão contadas.
     * @param palavras Um array de palavras a serem contadas no texto.
     * @return Um array de inteiros representando a contagem de cada palavra em palavras.
     */
    private static int[] countWords(String text, String[] words) {
        int[] wordCounts = new int[words.length];

        for (int i = 0; i < words.length; i++) {
            for (int j = 0; j < text.length(); j++) {
                if (text.charAt(j) == words[i].charAt(0) && j + words[i].length() < text.length()) {
                    int check = words[i].length();
                    boolean isEqual = true;

                    for (int k = 0; k < check; k++) {
                        if (words[i].charAt(k) != text.charAt(j + k)) {
                            isEqual = false;
                        }
                    }

                    if (isEqual) {
                        wordCounts[i]++;
                    }
                }
            }
        }

        return wordCounts;
    }

    /**
     * Conta as ocorrências de vogais, consoantes e tags HTML no conteúdo de uma página web.
     * 
     * @param url O endereço da página web.
     * @param texto O nome da página web (usado para a saída final).
     */
    private static void countElements(String url, String text) {
        String pageContent = httpRequest(url);

        char[] vowels = { 'a', 'e', 'i', 'o', 'u', '\u00E1', '\u00E9', '\u00ED', '\u00F3', '\u00FA', '\u00E0', '\u00E8', '\u00EC', '\u00F2', '\u00F9', '\u00E3', '\u00F5', '\u00E2', '\u00EA', '\u00EE', '\u00F4', '\u00FB' };
        char[] consonants = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z' };
        String[] tags = {"<br>", "<table>"};

        int[] vowelCounts = countLetters(pageContent, vowels);
        int[] consonantCounts = countLetters(pageContent, consonants);
        int totalConsonants = 0;
        int[] tagCounts = countWords(pageContent, tags);

        vowelCounts[0] -= (1 * tagCounts[1]);
        vowelCounts[1] -= (1 * tagCounts[1]);
        totalConsonants -= (3 * tagCounts[1]);
        totalConsonants -= (2 * tagCounts[0]);

        for (int i = 0; i < vowels.length; i++) {
            System.out.print(vowels[i] + "(" + vowelCounts[i] + ") ");
        }

        for (int i = 0; i < consonantCounts.length; i++) {
            totalConsonants += consonantCounts[i];
        }

        System.out.print("consoante(" + totalConsonants + ") ");

        for (int i = 0; i < tagCounts.length; i++) {
            System.out.print(tags[i] + "(" + tagCounts[i] + ") ");
        }

        System.out.println(text);
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
     * Método principal que inicia o programa e gerencia a entrada e saída.
     * Lê o nome da página e a URL, depois chama a função para contar os elementos.
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String text = sc.nextLine();
        String url;

        while (!isEnd(text)) {
            url = sc.nextLine();
            countElements(url, text);

            text = sc.nextLine();
        }

        sc.close();
    }
}