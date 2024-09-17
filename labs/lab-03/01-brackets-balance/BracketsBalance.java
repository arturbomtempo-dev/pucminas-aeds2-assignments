import java.util.Scanner;

/**
 * LAB03Q01 - Balanço Parênteses
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 01/09/2024
 */

public class BracketsBalance {
    /**
     * O método principal lê linhas de entrada contendo expressões matemáticas com parênteses
     * e verifica se os parênteses estão balanceados (ou seja, cada parêntese de abertura possui um
     * correspondente de fechamento e os parênteses estão na ordem correta).
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String expression = sc.nextLine();
            int openParenthesis = 0, closedParenthesis = 0;
            boolean isCorrect = true;

            if (!(expression.equals("FIM"))) {
                for (int i = 0; i < expression.length(); i++) {
                    char currentChar = expression.charAt(i);

                    if (currentChar == '(') {
                        openParenthesis++;
                    }

                    if (currentChar == ')') {
                        closedParenthesis++;

                        if (closedParenthesis > openParenthesis) {
                            isCorrect = false;
                        }
                    }
                }

                if (openParenthesis != closedParenthesis) {
                    isCorrect = false;
                }

                if (isCorrect) {
                    System.out.println("correto");
                } else {
                    System.out.println("incorreto");
                }
            }
        }

        sc.close();
    }
}