#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Código fonte - Implementação da Tabela Hash Indireta com Lista Simples Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Hash Table with Indirect Addressing and Flexible Linked List
 * @language C
 * @version 1.0
 */

typedef struct Cell {
    int element;
    struct Cell *next;
} Cell;

typedef struct List {
    Cell *first;
    Cell *last;
} List;

void initList(List *list) {
    list->first = NULL;
    list->last = NULL;
}

void insertStart(List *list, int value) {
    Cell *temp = (Cell *)malloc(sizeof(Cell));
    temp->element = value;
    temp->next = list->first;
    list->first = temp;

    if (list->last == NULL) {
        list->last = temp;
    }
}

void insertEnd(List *list, int value) {
    Cell *temp = (Cell *)malloc(sizeof(Cell));
    temp->element = value;
    temp->next = NULL;

    if (list->last == NULL) {
        list->first = temp;
        list->last = temp;
    } else {
        list->last->next = temp;
        list->last = temp;
    }
}

int removeStart(List *list) {
    if (list->first == NULL) {
        printf("Erro ao remover: Lista vazia\n");
        return -1;
    }

    Cell *temp = list->first;
    int element = temp->element;
    list->first = list->first->next;

    if (list->first == NULL) {
        list->last = NULL;
    }

    free(temp);

    return element;
}

int removeEnd(List *list) {
    if (list->first == NULL) {
        printf("Erro ao remover: Lista vazia\n");
        return -1;
    }

    Cell *temp = list->first;

    if (temp->next == NULL) {
        int element = temp->element;
        free(temp);
        list->first = NULL;
        list->last = NULL;
        return element;
    }

    while (temp->next != list->last) {
        temp = temp->next;
    }

    int element = list->last->element;
    free(list->last);
    list->last = temp;
    list->last->next = NULL;

    return element;
}

bool removeByValue(List *list, int value) {
    if (list->first == NULL) {
        printf("Erro ao remover: Lista vazia\n");
        return false;
    }

    Cell *prev = NULL;
    Cell *current = list->first;

    while (current != NULL) {
        if (current->element == value) {
            if (prev == NULL) {
                list->first = current->next;
                if (list->first == NULL) {
                    list->last = NULL;
                }
            } else {
                prev->next = current->next;
                if (current == list->last) {
                    list->last = prev;
                }
            }

            free(current);

            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

bool search(List *list, int value) {
    Cell *current = list->first;

    while (current != NULL) {
        if (current->element == value) {
            return true;
        }

        current = current->next;
    }

    return false;
}

void show(List *list) {
    Cell *current = list->first;
    printf("[");

    while (current != NULL) {
        printf("%d ", current->element);
        current = current->next;
    }

    printf("]\n");
}

typedef struct Hash {
    List *table;
    int size;
} Hash;

void initHash(Hash *hash, int size) {
    hash->size = size;
    hash->table = (List *)malloc(sizeof(List) * size);

    for (int i = 0; i < size; i++) {
        initList(&hash->table[i]);
    }
}

int hashFunction(Hash *hash, int value) { return value % hash->size; }

void insertStartHash(Hash *hash, int value) {
    int index = hashFunction(hash, value);
    insertStart(&hash->table[index], value);
}

bool searchHash(Hash *hash, int value) {
    int index = hashFunction(hash, value);
    return search(&hash->table[index], value);
}

bool removeHash(Hash *hash, int value) {
    int index = hashFunction(hash, value);
    return removeByValue(&hash->table[index], value);
}

int main() {
    Hash hashTable;
    initHash(&hashTable, 7);

    printf("Inserindo valores...\n");
    insertStartHash(&hashTable, 10);
    insertStartHash(&hashTable, 23);
    insertStartHash(&hashTable, 36);
    insertStartHash(&hashTable, 49);
    insertStartHash(&hashTable, 15);
    insertStartHash(&hashTable, 64);

    printf("\nTabela Hash após inserções:\n");
    for (int i = 0; i < 7; i++) {
        printf("Índice %d: ", i);
        show(&hashTable.table[i]);
    }

    printf("\nPesquisando valores...\n");
    printf("Valor 23 encontrado? %s\n",
           searchHash(&hashTable, 23) ? "Sim" : "Não");
    printf("Valor 99 encontrado? %s\n",
           searchHash(&hashTable, 99) ? "Sim" : "Não");

    printf("\nRemovendo valores...\n");
    printf("Valor 23 removido? %s\n",
           removeHash(&hashTable, 23) ? "Sim" : "Não");
    printf("Valor 99 removido? %s\n",
           removeHash(&hashTable, 99) ? "Sim" : "Não");

    printf("\nTabela Hash após remoções:\n");
    for (int i = 0; i < 7; i++) {
        printf("Índice %d: ", i);
        show(&hashTable.table[i]);
    }

    return 0;
}