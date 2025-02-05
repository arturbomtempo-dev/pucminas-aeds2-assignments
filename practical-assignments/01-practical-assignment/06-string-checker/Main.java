import java.util.Scanner;

/**
 * TP01Q06 - Is
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 30/08/2024
 */

public class Main {
    public static boolean isVowel(String input) {
        boolean vowel = true;

        for (int i = 0; i < input.length(); i++) {
            if (!(input.charAt(i) == 'a' || input.charAt(i) == 'e' || input.charAt(i) == 'i' || input.charAt(i) == 'o' || input.charAt(i) == 'u' || input.charAt(i) == 'A' || input.charAt(i) == 'E' || input.charAt(i) == 'I' || input.charAt(i) == 'O' || input.charAt(i) == 'U')) {
                vowel = false;
                i = input.length();
            }
        }

        return vowel;
    }
    
    public static boolean isConsonant(String input) {
        boolean consonant = true;

        for (int i = 0; i < input.length(); i++) {
            if (!(input.charAt(i) == 'a' || input.charAt(i) == 'e' || input.charAt(i) == 'i' || input.charAt(i) == 'o' || input.charAt(i) == 'u' || input.charAt(i) == 'A' || input.charAt(i) == 'E' || input.charAt(i) == 'I' || input.charAt(i) == 'O' || input.charAt(i) == 'U')) {
                consonant = false;
                i = input.length();
            } else {
                if (input.charAt(i) >= 65 && input.charAt(i) <= 90 || input.charAt(i) >= 97 && input.charAt(i) <= 22) {
                    consonant = true;
                } else {
                    consonant = false;
                    i = input.length();
                }
            }
        }

        return consonant;
    }
    
    public static boolean isInteger(String input) {
        boolean integer = true;

        for (int i = 0; i < input.length(); i++) {
            if (input.charAt(i) <= 47 || input.charAt(i) >= 58) {
                integer = false;
                i = input.length();
            }
        }

        return integer;
    }
    
    public static boolean isReal(String input) {
        boolean real = true;
        int dotCount = 0, commaCount = 0;
    
        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
    
            if (!(c >= '0' && c <= '9')) {
                if (c == '.') {
                    dotCount++;
                } else if (c == ',') {
                    commaCount++;
                } else {
                    real = false;
                    i = input.length();
                }
            }
    
            if (dotCount > 1 || commaCount > 1) {
                real = false;
                i = input.length();
            }
        }
    
        if (input.length() > 0) {
            char lastChar = input.charAt(input.length() - 1);

            if (lastChar == '.' || lastChar == ',') {
                real = false;
            }
        }
    
        return real;
    }
    
    public static boolean isEnd(String input) {
        return input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M';
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String input = sc.nextLine();
            if (!isEnd(input)) {
                String result = "";

                if (isVowel(input)) {
                    result += "SIM ";
                } else {
                    result += "NAO ";
                }

                if (isConsonant(input)) {
                    result += "SIM ";
                } else {
                    result += "NAO ";
                }

                if (isInteger(input)) {
                    result += "SIM ";
                } else {
                    result += "NAO ";
                }

                if (isReal(input)) {
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