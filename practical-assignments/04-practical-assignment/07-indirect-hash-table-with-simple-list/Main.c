#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

/**
 * TP04Q07 - Tabela Hash Indireta com Lista Simples
 *
 * @author Artur Bomtempo Colen
 * @version 1.0, 05/12/2024
 */

int comparisons = 0;
int movements = 0;

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef struct Pokemon {
    int id;
    int generation;
    char name[100];
    char description[100];
    char type[2][100];
    char abilities[20][100];
    double weight;
    double height;
    int captureRate;
    bool isLegendary;
    Date captureDate;
} Pokemon;

Pokemon *search(Pokemon *pokemons, int id) {
    Pokemon *pokemon;

    for (int i = 0; i < 801; i++) {
        if (pokemons[i].id == id) {
            pokemon = &pokemons[i];
        }
    }

    return pokemon;
}

void removeOccurrences(char *str, char character) {
    int i, j = 0;
    size_t length = strlen(str);

    for (i = 0; i < length; i++) {
        if (str[i] != character) {
            str[j++] = str[i];
        }
    }

    str[j] = '\0';
}

char *removeAttribute(char **str, char delimiter) {
    char *start = *str;
    char *end = *str;

    if (*start == '"') {
        start++;
        end = strchr(start, '"');
    } else {
        end = strchr(start, delimiter);
    }

    if (end != NULL) {
        *end = '\0';
        *str = end + 1;
    } else {
        *str = start + strlen(start);
    }

    return start;
}

Pokemon *readCsv(char fileName[]) {
    Pokemon *pokemons = (Pokemon *)malloc(801 * sizeof(Pokemon));

    if (!pokemons) {
        printf("Erro de alocação de memória.\n");
    }

    FILE *file = fopen(fileName, "r");

    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        free(pokemons);
    }

    char line[500];
    fgets(line, sizeof(line), file);

    int index = 0;

    while (fgets(line, sizeof(line), file) != NULL && index < 801) {
        Pokemon *temp = &pokemons[index];
        char *token = line;

        temp->id = atoi(removeAttribute(&token, ','));
        temp->generation = atoi(removeAttribute(&token, ','));
        strcpy(temp->name, removeAttribute(&token, ','));
        strcpy(temp->description, removeAttribute(&token, ','));
        strcpy(temp->type[0], removeAttribute(&token, ','));
        strcpy(temp->type[1], removeAttribute(&token, ','));

        char *abilitiesString = removeAttribute(&token, ',');

        removeOccurrences(abilitiesString, '[');
        removeOccurrences(abilitiesString, ']');
        removeOccurrences(abilitiesString, '\'');

        char *abilitiesToken = abilitiesString;
        int abilitiesIndex = 0;

        while (*abilitiesToken != '\0' && abilitiesIndex < 10) {
            while (isspace(*abilitiesToken)) {
                abilitiesToken++;
            }

            char *startAbilities = abilitiesToken;
            char *endAbilities;

            if (*startAbilities == '\'') {
                startAbilities++;
                endAbilities = strchr(startAbilities, '\'');
            } else {
                endAbilities = strchr(startAbilities, ',');
            }

            if (endAbilities != NULL) {
                *endAbilities = '\0';
                strcpy(temp->abilities[abilitiesIndex], startAbilities);
                abilitiesIndex++;
                abilitiesToken = endAbilities + 1;
            } else {
                strcpy(temp->abilities[abilitiesIndex], startAbilities);
                break;
            }
        }

        char *trash = removeAttribute(&token, ',');

        temp->weight = atof(removeAttribute(&token, ','));
        temp->height = atof(removeAttribute(&token, ','));
        temp->captureRate = atoi(removeAttribute(&token, ','));

        int isLegendary = atoi(removeAttribute(&token, ','));

        if (isLegendary == 0) {
            temp->isLegendary = false;
        } else {
            temp->isLegendary = true;
        }

        sscanf(removeAttribute(&token, '/'), "%d", &temp->captureDate.day);
        sscanf(removeAttribute(&token, '/'), "%d", &temp->captureDate.month);
        sscanf(removeAttribute(&token, '/'), "%d", &temp->captureDate.year);

        index++;
    }

    fclose(file);

    return pokemons;
}

void saveExecutionFile(const char *Filename, long totalTime) {
    FILE *file = fopen(Filename, "w+");

    if (file == NULL) {
        printf("Erro ao gerar o arquivo.\n");
    } else {
        fprintf(file, "847235\t%d\t%d\t%ldms", comparisons, movements,
                totalTime);
        fclose(file);
    }
}

typedef struct Cell {
    Pokemon *pokemon;
    struct Cell *next;
} Cell;

Cell *newCell(Pokemon *pokemon) {
    Cell *temp = (Cell *)malloc(sizeof(Cell));
    temp->pokemon = pokemon;
    temp->next = NULL;
    return temp;
}

typedef struct List {
    struct Cell *first, *last;
    int size;
} List;

List *newList() {
    List *temp = (List *)malloc(sizeof(List));
    ;
    temp->first = temp->last = newCell(NULL);
    temp->size = 0;
    return temp;
}

void insertStart(List *list, Pokemon *pokemon) {
    Cell *temp = newCell(pokemon);

    temp->next = list->first;
    list->first->pokemon = pokemon;
    list->first = temp;
    list->size++;
}

void insertEnd(List *list, Pokemon *pokemon) {
    list->last->next = newCell(pokemon);
    list->last = list->last->next;
    list->size++;
}

bool searchList(List *list, char *name) {
    Cell *i;
    bool response = false;

    for (i = list->first->next; i != NULL; i = i->next) {
        comparisons++;

        if (strcmp(i->pokemon->name, name) == 0) {
            response = true;
        }
    }

    return response;
}

List **table;
int size;

void indirectHashList(int n) {
    size = n;
    table = (List **)malloc(size * sizeof(List *));

    for (int i = 0; i < size; i++) {
        table[i] = newList();
    }
}

void newIndirectHashList() { indirectHashList(21); }

int h(char *name) {
    int sum = 0;
    for (int i = 0; i < strlen(name); sum += (int)name[i], i++);
    return sum % size;
}

int hashSearch(char *name) {
    int position = h(name);
    bool response = searchList(table[position], name);
    return response ? position : -1;
}

void hashInsert(Pokemon *pokemon) {
    int position = h(pokemon->name);
    insertStart(table[position], pokemon);
}

bool isEnd(char *input) {
    return (strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' &&
            input[2] == 'M');
}

int main() {
    clock_t startClock, endClock;
    double totalTime;

    Pokemon *pokemons = readCsv("../tmp/pokemon.csv");

    newIndirectHashList();

    int id;
    char input[30];

    startClock = clock();

    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);
        hashInsert(search(pokemons, id));
    }

    while (scanf("%s", input) && !isEnd(input)) {
        int response = hashSearch(input);
        response != -1 ? printf("=> %s: (Posicao: %d) SIM\n", input, response)
                       : printf("=> %s: NAO\n", input);
    }

    endClock = clock();
    totalTime = ((double)(endClock - startClock));

    saveExecutionFile("847235_hashIndireta.txt", totalTime);

    free(pokemons);

    return 0;
}