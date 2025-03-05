#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Código fonte - Implementação da Tabela Hash Direta com Rehash
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Hash Table with Direct Addressing and Rehashing
 * @language C
 * @version 1.0
 */

typedef struct {
    int *table;
    int m;
} Hash;

void initHash(Hash *hash, int m) {
    hash->m = m;
    hash->table = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        hash->table[i] = -1;
    }
}

int h(Hash *hash, int value) { return value % hash->m; }

int reh(Hash *hash, int value) { return ++value % hash->m; }

void insert(Hash *hash, int value) {
    int i = h(hash, value);

    if (value == -1) {
        printf("Favor inserir um valor.\n");
    } else if (hash->table[i] == -1) {
        hash->table[i] = value;
    } else {
        i = reh(hash, i);

        if (hash->table[i] == -1) {
            hash->table[i] = value;
        }
    }
}

bool search(Hash *hash, int value) {
    int i = h(hash, value);
    bool found = false;

    if (hash->table[i] == value) {
        found = true;
    } else {
        i = reh(hash, i);

        if (hash->table[i] == value) {
            found = true;
        }
    }

    return found;
}

bool removal(Hash *hash, int value) {
    int i = h(hash, value);
    bool removed = false;

    if (hash->table[i] == value) {
        hash->table[i] = -2;
        removed = true;
    } else {
        i = reh(hash, i);

        if (hash->table[i] == value) {
            hash->table[i] = -2;
            removed = true;
        }
    }

    return removed;
}

void show(Hash *hash) {
    printf("Índice\tValor\n");

    for (int i = 0; i < hash->m; i++) {
        printf("%d\t%d\n", i, hash->table[i]);
    }
}

void freeHash(Hash *hash) { free(hash->table); }

int main() {
    Hash hashTable;
    initHash(&hashTable, 13);

    printf("Inserindo valores...\n");
    insert(&hashTable, 10);
    insert(&hashTable, 23);
    insert(&hashTable, 36);
    insert(&hashTable, 49);
    insert(&hashTable, 15);
    insert(&hashTable, 64);

    printf("\nTabela Hash após inserções:\n");
    show(&hashTable);

    printf("\nPesquisando valores...\n");
    printf("Valor 23 encontrado? %s\n",
           search(&hashTable, 23) ? "true" : "false");
    printf("Valor 99 encontrado? %s\n",
           search(&hashTable, 99) ? "true" : "false");

    printf("\nRemovendo valores...\n");
    printf("Valor 23 removido? %s\n",
           removal(&hashTable, 23) ? "true" : "false");
    printf("Valor 99 removido? %s\n",
           removal(&hashTable, 99) ? "true" : "false");

    printf("\nTabela Hash após remoções:\n");
    show(&hashTable);

    freeHash(&hashTable);

    return 0;
}