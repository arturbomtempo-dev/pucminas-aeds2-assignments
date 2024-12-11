import java.util.Scanner;

/**
 * BEE 1120
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/09/2024
 */

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String D = sc.next();
        String N = sc.next();

        while (!(D.equals("0") && N.equals("0"))) {
            char valueToRemove = D.charAt(0);
            String newExpression = "";
            boolean nonZeroFound = false;

            for (int i = 0; i < N.length(); i++) {
                char currentValue = N.charAt(i);

                if (currentValue != valueToRemove) {
                    if (currentValue != '0') {
                        newExpression += currentValue;
                        nonZeroFound = true;
                    } else if (nonZeroFound) {
                        newExpression += currentValue;
                    }
                }
            }

            if (newExpression.length() > 0) {
                System.out.println(newExpression);
            } else {
                System.out.println("0");
            }

            D = sc.next();
            N = sc.next();
        }

        sc.close();
    }
}