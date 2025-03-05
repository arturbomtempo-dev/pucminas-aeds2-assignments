/**
 * Código fonte - Implementação da Tabela Hash Direta com Rehash
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Hash Table with Direct Addressing and Rehashing
 * @language Java
 * @version 1.0
 */

class Hash {
    int table[];
    int m;

    public Hash() {
        this.m = 13;
    }

    public Hash(int m) {
        this.m = m;
        this.table = new int[this.m];

        for (int i = 0; i < m; i++) {
            table[i] = -1;
        }
    }

    public int hash(int value) {
        return value % m;
    }

    public int rehash(int value) {
        return ++value % m;
    }

    public void insert(int value) {
        if (value == -1) {
            System.out.println("Favor inserir um valor.");
        } else {
            int i = hash(value);

            if (table[i] == -1) {
                table[i] = value;
            } else {
                i = rehash(value);

                if (table[i] == -1) {
                    table[i] = value;
                }
            }
        }
    }

    public boolean search(int value) {
        int i = hash(value);
        boolean found = false;

        if (table[i] == value) {
            found = true;
        } else if (table[i] != -1) {
            i = rehash(value);

            if (table[i] == value) {
                found = true;
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
            i = rehash(value);

            if (table[i] == value) {
                table[i] = -2;
                removed = true;
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
        Hash hashTable = new Hash(13);

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