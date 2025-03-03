import java.util.*;

/**
 * Sorvete
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 12/09/2024
 */

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int test = 1;
        boolean persist = true;

        while (persist && sc.hasNext()) {
            int P = sc.nextInt();
            int S = sc.nextInt();

            if (P == 0 && S == 0) {
                persist = false;
            } else {
                int[][] intervals = new int[S][2];

                for (int i = 0; i < S; i++) {
                    intervals[i][0] = sc.nextInt();
                    intervals[i][1] = sc.nextInt();
                }

                Arrays.sort(intervals, Comparator.comparingInt(a -> a[0]));

                List<int[]> result = new ArrayList<>();
                int startCurrent = intervals[0][0];
                int endCurrent = intervals[0][1];

                for (int i = 1; i < S; i++) {
                    if (intervals[i][0] <= endCurrent) {
                        endCurrent = Math.max(endCurrent, intervals[i][1]);
                    } else {
                        result.add(new int[]{startCurrent, endCurrent});
                        startCurrent = intervals[i][0];
                        endCurrent = intervals[i][1];
                    }
                }

                result.add(new int[]{startCurrent, endCurrent});

                System.out.println("Teste " + test);

                for (int[] interval : result) {
                    System.out.println(interval[0] + " " + interval[1]);
                }

                test++;
            }
        }

        sc.close();
    }
}