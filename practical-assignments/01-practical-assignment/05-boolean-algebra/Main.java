import java.util.Scanner;

/**
 * TP01Q05 - Algebra Boleana
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 28/08/2024
 */

public class Main {
    private static String evaluateAndExpression(String expression) {
        String processedExpression = "";

        for (int i = 0; i < expression.length(); i++) {
            if (expression.charAt(i) == 'a' && (expression.charAt(i + 4) == '1' || expression.charAt(i + 4) == '0')
                    && (expression.charAt(i + 6) == '1' || expression.charAt(i + 6) == '0')) {
                if (expression.charAt(i + 7) == ')') {
                    processedExpression += (expression.charAt(i + 4) == '1' && expression.charAt(i + 6) == '1') ? 1 : 0;
                    i += 7;
                } else if (expression.charAt(i + 9) == ')') {
                    processedExpression += (expression.charAt(i + 4) == '1' && expression.charAt(i + 6) == '1'
                            && expression.charAt(i + 8) == '1') ? 1 : 0;
                    i += 9;
                } else if (expression.charAt(i + 11) == ')') {
                    processedExpression += (expression.charAt(i + 4) == '1' && expression.charAt(i + 6) == '1'
                            && expression.charAt(i + 8) == '1' && expression.charAt(i + 10) == '1') ? 1 : 0;
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

    private static String evaluateOrExpression(String expression) {
        String processedExpression = "";

        for (int i = 0; i < expression.length(); i++) {
            if (expression.charAt(i) == 'o' && expression.charAt(i + 1) == 'r'
                    && (expression.charAt(i + 3) == '1' || expression.charAt(i + 3) == '0')
                    && (expression.charAt(i + 5) == '1' || expression.charAt(i + 5) == '0')) {
                if (expression.charAt(i + 6) == ')') {
                    processedExpression += (expression.charAt(i + 3) == '1' || expression.charAt(i + 5) == '1') ? 1 : 0;
                    i += 6;
                } else if (expression.charAt(i + 8) == ')') {
                    processedExpression += (expression.charAt(i + 3) == '1' || expression.charAt(i + 5) == '1'
                            || expression.charAt(i + 7) == '1') ? 1 : 0;
                    i += 8;
                } else if (expression.charAt(i + 10) == ')') {
                    processedExpression += (expression.charAt(i + 3) == '1' || expression.charAt(i + 5) == '1'
                            || expression.charAt(i + 7) == '1' || expression.charAt(i + 9) == '1') ? 1 : 0;
                    i += 10;
                }
            } else {
                processedExpression += expression.charAt(i);
            }
        }

        return processedExpression;
    }

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

    public static boolean isEnd(int input) {
        return input == 0;
    }

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