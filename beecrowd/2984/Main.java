import java.util.*;;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            int open = 0, close = 0;

            for (int i = 0; i < line.length(); i++) {
                if (line.charAt(i) == '(') {
                    open++;
                } else if (line.charAt(i) == ')' && open >= 1) {
                    close++;
                }
            }

            if (open > close) {
                int pendingIssues = open - close;
                System.out.println("Ainda temos " + pendingIssues + " assunto(s) pendente(s)!");
            } else {
                System.out.println("Partiu RU!");
            }
        }

        sc.close();
    }
}