#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *table;
    int m1, m2, m, reservation;
} Hash;

void initHash(Hash *hash, int m1, int m2) {
    hash->m1 = m1;
    hash->m2 = m2;
    hash->m = m1 + m2;
    hash->reservation = 0;

    hash->table = (int *) malloc(hash->m * sizeof(int));
    
    for (int i = 0; i < hash->m; i++) {
        hash->table[i] = -1;
    }
}

int h(Hash *hash, int value) {
    return value % hash->m1;
}

void insert(Hash *hash, int value) {
    int i = h(hash, value);

    if (value == -1) {
        printf("Favor inserir um valor.\n");
    } else if (hash->table[i] == -1) {
        hash->table[i] = value;
    } else if (hash->reservation < hash->m2) {
        hash->table[hash->m1 + hash->reservation] = value;
        hash->reservation++;
    } else {
        printf("Erro ao inserir elemento na tabela hash.\n");
    }
}

bool search(Hash *hash, int value) {
    int i = h(hash, value);

    if (hash->table[i] == value) {
        return true;
    }

    for (int j = 0; j < hash->reservation; j++) {
        if (hash->table[hash->m1 + j] == value) {
            return true;
        }
    }

    return false;
}

bool removal(Hash *hash, int value) {
    int i = h(hash, value);

    if (hash->table[i] == value) {
        hash->table[i] = -2;
        return true;
    }

    for (int j = 0; j < hash->reservation; j++) {
        if (hash->table[hash->m1 + j] == value) {
            hash->table[hash->m1 + j] = -2;
            return true;
        }
    }

    return false;
}

void show(Hash *hash) {
    printf("Índice\tValor\n");
    for (int i = 0; i < hash->m; i++) {
        printf("%d\t%d\n", i, hash->table[i]);
    }
}

void freeHash(Hash *hash) {
    free(hash->table);
}

int main() {
    Hash hashTable;
    initHash(&hashTable, 13, 7);

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
    printf("Valor 23 encontrado? %s\n", search(&hashTable, 23) ? "true" : "false");
    printf("Valor 99 encontrado? %s\n", search(&hashTable, 99) ? "true" : "false");

    printf("\nRemovendo valores...\n");
    printf("Valor 23 removido? %s\n", removal(&hashTable, 23) ? "true" : "false");
    printf("Valor 99 removido? %s\n", removal(&hashTable, 99) ? "true" : "false");

    printf("\nTabela Hash após remoções:\n");
    show(&hashTable);

    // Libera memória alocada para a tabela hash
    freeHash(&hashTable);

    return 0;
}