import java.util.Scanner;

/**
 * TP01Q05 - Algebra Boleana
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 28/08/2024
 */

public class BooleanAlgebra {
    /**
     * Esse método processa uma expressão booleana que inclui um operador AND 
     * e a substitui pelo resultado binário apropriado (1 ou 0) com base nos 
     * valores de dos operandos na expressão.
     *
     * @param expression A expressão booleana que contém uma operação AND.
     * @return Uma string que representa a expressão com a operação AND avaliada.
     */
    private static String evaluateAndExpression(String expression) {
        String processedExpression = "";

        for (int i = 0; i < expression.length(); i++) {
            if (expression.charAt(i) == 'a' && (expression.charAt(i + 4) == '1' || expression.charAt(i + 4) == '0') && (expression.charAt(i + 6) == '1' || expression.charAt(i + 6) == '0')) {
                if (expression.charAt(i + 7) == ')') {
                    processedExpression += (expression.charAt(i + 4) == '1' && expression.charAt(i + 6) == '1') ? 1 : 0;
                    i += 7;
                } else if (expression.charAt(i + 9) == ')') {
                    processedExpression += (expression.charAt(i + 4) == '1' && expression.charAt(i + 6) == '1' && expression.charAt(i + 8) == '1') ? 1 : 0;
                    i += 9;
                } else if (expression.charAt(i + 11) == ')') {
                    processedExpression += (expression.charAt(i + 4) == '1' && expression.charAt(i + 6) == '1' && expression.charAt(i + 8) == '1' && expression.charAt(i + 10) == '1') ? 1 : 0;
                    i += 11;
                } else {
                    processedExpression += expression.charAt(i);
                }
            } else {
                processedExpression += expression.charAt(i);
            }
        }

        return processedExpression;
    }

    /**
     * Esse método processa uma expressão booleana que inclui um operador OR e a 
     * substitui pelo resultado binário apropriado (1 ou 0) com base nos valores
     * dos operandos na expressão.
     *
     * @param expression A expressão booleana que contém uma operação OR.
     * @return Uma nova string que representa a expressão com a operação OR avaliada.
     */
    private static String evaluateOrExpression(String expression) {
        String processedExpression = "";

        for (int i = 0; i < expression.length(); i++) {
            if (expression.charAt(i) == 'o' && expression.charAt(i + 1) == 'r' && (expression.charAt(i + 3) == '1' || expression.charAt(i + 3) == '0') && (expression.charAt(i + 5) == '1' || expression.charAt(i + 5) == '0')) {
                if (expression.charAt(i + 6) == ')') {
                    processedExpression += (expression.charAt(i + 3) == '1' || expression.charAt(i + 5) == '1') ? 1 : 0;
                    i += 6;
                } else if (expression.charAt(i + 8) == ')'){
                    processedExpression += (expression.charAt(i + 3) == '1' || expression.charAt(i + 5) == '1' || expression.charAt(i + 7) == '1') ? 1 : 0;
                    i += 8;
                } else if (expression.charAt(i + 10) == ')') {
                    processedExpression += (expression.charAt(i + 3) == '1' || expression.charAt(i + 5) == '1' || expression.charAt(i + 7) == '1' || expression.charAt(i + 9) == '1') ? 1 : 0;
                    i += 10;
                }
            } else {
                processedExpression += expression.charAt(i);
            }
        }

        return processedExpression;
    }

    /**
     * Esse método processa uma expressão booleana que inclui um operador NOT 
     * e a substitui pelo resultado binário apropriado (1 ou 0), invertendo o 
     * valor do operando na expressão.
     *
     * @param expression A expressão booleana que contém uma operação NOT.
     * @return Uma nova string que representa a expressão com a operação NOT avaliada.
     */
    private static String evaluateNotExpression(String expression) {
        String processedExpression = "";

        for (int i = 0; i < expression.length(); i++) {
            if (expression.charAt(i) == 'n' && (expression.charAt(i + 4) == '1' || expression.charAt(i + 4) == '0')) {
                processedExpression += expression.charAt(i + 4) == '1' ? 0 : 1;
                i += 5;
            } else {
                processedExpression += expression.charAt(i);
            }
        }

        return processedExpression;
    }

    /**
     * Esse método substitui as variáveis (A, B, C) na expressão booleana por seus respectivos valores.
     * 
     * Esse método substitui as variáveis A, B e C na expressão pelos valores fornecidos na 
     * entradas, permitindo que a expressão seja avaliada com valores booleanos específicos.
     *
     * @param inputs Um array de inteiros (0 ou 1) que representa os valores booleanos das variáveis A, B e C.
     * @param expression A expressão booleana que contém as variáveis A, B e C.
     * @return Uma nova string que representa a expressão com as variáveis substituídas por seus valores correspondentes.
     */
    private static String replaceVariablesWithValues(int[] inputs, String expression) {
        String processedExpression = "";

        for (int i = 0; i < expression.length(); i++) {
            if (expression.charAt(i) != ' ') {
                if (expression.charAt(i) == 'A') {
                    processedExpression += inputs[0];
                } else if (expression.charAt(i) == 'B') {
                    processedExpression += inputs[1];
                } else if (expression.charAt(i) == 'C') {
                    processedExpression += inputs[2];
                } else {
                    processedExpression += expression.charAt(i);
                }
            }
        }

        return processedExpression;
    }

    /**
     * Esse método processa a expressão booleana avaliando todas as operações (AND, OR, NOT) 
     * dentro dela na ordem correta, usando uma pilha para manter o controle das operações e 
     * suas posições na expressão.
     *
     * @param expression A expressão booleana a ser avaliada.
     * @return Uma cadeia de caracteres que representa o resultado final avaliado da expressão booleana.
     */
    private static String evaluateBooleanExpression(String expression) {
        int openParenthesesCount = 0;

        for (int i = 0; i < expression.length(); i++) {
            if (expression.charAt(i) == '(') {
                openParenthesesCount++;
            }
        }

        char[] operationStack = new char[openParenthesesCount];

        for (int i = 0; i < expression.length() - 2; i++) {
            if (expression.charAt(i + 2) == 't') {
                operationStack[--openParenthesesCount] = 'n';
            } else if (expression.charAt(i + 2) == 'd') {
                operationStack[--openParenthesesCount] = 'a';
            } else if (expression.charAt(i + 1) == 'r') {
                operationStack[--openParenthesesCount] = 'o';
            }
        }

        for (int i = 0; i < operationStack.length; i++) {
            if (operationStack[i] == 'a') {
                expression = evaluateAndExpression(expression);
            } else if (operationStack[i] == 'n') {
                expression = evaluateNotExpression(expression);
            } else {
                expression = evaluateOrExpression(expression);
            }
        }

        return expression;
    }

    /**
     * Verifica se o valor de entrada é zero, indicando o término da execução.
     * 
     * @param input O valor de entrada a ser verificado.
     * @return {@code true} se o valor for zero, {@code false} caso contrário.
     */
    public static boolean isEnd(int input) {
        return input == 0;
    }

    /**
     * Método principal que recebe a quantidade de portas que serão lidas,
     * processa os dados que entraram e retorna o valor final (0 ou 1) correspondente
     * ao resultado da expressão. O programa executa até que o usuário digite 0 na entrada
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int numberOfInputs = sc.nextInt();
        String expression;
        int[] inputValues = new int[3];

        while (!isEnd(numberOfInputs)) {
            for (int i = 0; i < numberOfInputs; i++) {
                inputValues[i] = sc.nextInt();
            }

            expression = sc.nextLine();
            expression = replaceVariablesWithValues(inputValues, expression);
            expression = evaluateBooleanExpression(expression);

            System.out.println(expression);

            numberOfInputs = sc.nextInt();
        }

        sc.close();
    }
}