class Hash {
    int table[];
    int m1, m2, m, reservation;

    public Hash() {
        this.m1 = 13;
        this.m2 = 7;
    }

    public Hash(int m1, int m2) {
        this.m1 = m1;
        this.m2 = m2;
        this.m = m1 + m2;
        this.table = new int[this.m];

        for (int i = 0; i < m1; i++) {
           table[i] = -1;
        }

        this.reservation = 0;
    }

    public int hash(int value) {
        return value % m1;
    }

    public void insert(int value) {
        int i = hash(value);

        if (value == -1) {
            System.out.println("Favor inserir um valor.");
        } else if (table[i] == -1) {
            table[i] = value;
        } else if (reservation < m2) {
            table[m1 + reservation] = value;
            reservation++;
        } else {
            System.out.println("Erro ao inserir elemento na tabela hash.");
        }
    }

    public boolean search(int value) {
        int i = hash(value);
        boolean found = false;

        if (table[i] == value) {
            found = true;
        } else if (table[i] != -1) {
            for (int j = 0; j < reservation; j++) {
                if (table[m1 + j] == value) {
                    found = true;
                    j = reservation;
                }
            }
        }

        return found;
    }

    public boolean removal(int value) {
        int i = hash(value);
        boolean removed = false;

        if (table[i] == value) {
            table[i] = -2;
            removed = true;
        } else if (table[i] != -1) {
            for (int j = 0; j < reservation; j++) {
                if (table[m1 + j] == value) {
                    table[m1 + j] = -2;
                    removed = true;
                    j = reservation;
                }
            }
        }

        return removed;
    }

    public void show() {
        System.out.println("Índice\tValor");

        for (int i = 0; i < m; i++) {
            System.out.println(i + "\t" + table[i]);
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Hash hashTable = new Hash(13, 7);

        System.out.println("Inserindo valores...");
        hashTable.insert(10);
        hashTable.insert(23);
        hashTable.insert(36);
        hashTable.insert(49);
        hashTable.insert(15);
        hashTable.insert(64);

        System.out.println("\nTabela Hash após inserções:");
        hashTable.show();

        System.out.println("\nPesquisando valores...");
        System.out.println("Valor 23 encontrado? " + hashTable.search(23));
        System.out.println("Valor 99 encontrado? " + hashTable.search(99));

        System.out.println("\nRemovendo valores...");
        System.out.println("Valor 23 removido? " + hashTable.removal(23));
        System.out.println("Valor 99 removido? " + hashTable.removal(99));

        System.out.println("\nTabela Hash após remoções:");
        hashTable.show();
    }
}