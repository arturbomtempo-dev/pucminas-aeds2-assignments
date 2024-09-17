import java.util.Scanner;

/**
 * Desempilhando Caixas
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 15/09/2024
 */

public class UnpackingBoxes {
    /**
     * Método principal que lida com a leitura da entrada, o processamento das pilhas e a 
     * impressão do número de caixas que precisam ser removidas.
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int boxCount = sc.nextInt();
        int stackCount = sc.nextInt();
        int[][] stacks = new int[boxCount][stackCount];
        int boxesInStack;
        int removalCount;
        int box1Index = 0;

        while (boxCount != 0 || stackCount != 0) {
            for (int j = 0; j < stackCount; j++) {
                boxesInStack = sc.nextInt();

                for (int i = 0; i < boxesInStack; i++) {
                    stacks[i][j] = sc.nextInt();
                }

                for (int i = boxesInStack; i < boxCount; i++) {
                    stacks[i][j] = 0;
                }
            }

            boolean found = false;

            for (int i = 0; i < boxCount && !found; i++) {
                for (int j = 0; j < stackCount && !found; j++) {
                    if (stacks[i][j] == 1) {
                        found = true;
                        box1Index = i;
                    }
                }
            }

            removalCount = 0;
            int i = boxCount - 1;
            int j = 0;
            found = false;

            while (!found) {
                while (i >= box1Index && !found) {
                    if (stacks[i][j] == 1) {
                        found = true;
                    }

                    if (stacks[i][j] != 0 && !found) removalCount++;

                    i--;
                }

                j++;
                i = boxCount - 1;
            }

            System.out.println(removalCount);

            boxCount = sc.nextInt();
            stackCount = sc.nextInt();
        }

        sc.close();
    }
}