import java.util.Scanner;

/**
 * BEE 1237
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 18/09/2024
 */

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        while (sc.hasNextLine()) {
            String s1 = sc.nextLine();
            String s2 = sc.nextLine();
            
            int maxLength = 0;
            int len1 = s1.length();
            int len2 = s2.length();
            
            for (int i = 0; i < len1; i++) {
                for (int j = 0; j < len2; j++) {
                    int k = 0;

                    while (i + k < len1 && j + k < len2 && s1.charAt(i + k) == s2.charAt(j + k)) {
                        k++;
                    }
                    
                    if (k > maxLength) {
                        maxLength = k;
                    }
                }
            }
            
            System.out.println(maxLength);
        }
        
        sc.close();
    }
}