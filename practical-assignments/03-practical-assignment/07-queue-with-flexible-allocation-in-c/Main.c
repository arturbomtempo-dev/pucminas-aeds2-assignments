#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * TP03Q07 - Fila com Alocação Flexível em C
 *
 * @author Artur Bomtempo Colen
 * @version 1.0, 08/11/2024
 */

typedef struct Date {
    int dia;
    int mes;
    int ano;
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

        sscanf(removeAttribute(&token, '/'), "%d", &temp->captureDate.dia);
        sscanf(removeAttribute(&token, '/'), "%d", &temp->captureDate.mes);
        sscanf(removeAttribute(&token, '/'), "%d", &temp->captureDate.ano);

        index++;
    }

    fclose(file);

    return pokemons;
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

typedef struct Queue {
    struct Cell *first, *last;
    int size;
} Queue;

Queue newQueue() {
    Queue temp;
    temp.first = temp.last = newCell(NULL);
    temp.size = 0;
    return temp;
}

Pokemon *removal(Queue *queue) {
    if (queue->first == queue->last) {
        printf("\nA queue está vazia.\n");
    }

    Cell *temp = queue->first;
    queue->first = queue->first->next;
    queue->size--;

    free(temp);

    return queue->first->pokemon;
}

void insert(Queue *queue, Pokemon *pokemon) {
    if (queue->size > 5 - 1) {
        removal(queue);
    }

    queue->last->next = newCell(pokemon);
    queue->last = queue->last->next;
    queue->size++;

    Cell *i = queue->first->next;
    int sum = 0;
    int k = 0;

    while (i != NULL) {
        sum += i->pokemon->captureRate;
        k++;
        i = i->next;
    }

    if (k > 0) {
        int roundedAverage = (int)round((double)sum / k);
        printf("Média: %d\n", roundedAverage);
    }
}

void displayInformation(Queue *f) {
    Cell *i;
    int count = 0;

    for (i = f->first->next; i != NULL; i = i->next) {
        printf("[%d] ", count++);
        printf("[#%d -> %s: %s - ", i->pokemon->id, i->pokemon->name,
               i->pokemon->description);

        printf("['%s'", i->pokemon->type[0]);

        if (strlen(i->pokemon->type[1]) > 0) {
            printf(", '%s'", i->pokemon->type[1]);
        }

        printf("] - [");

        for (int j = 0; strlen(i->pokemon->abilities[j]) > 0; j++) {
            printf("'%s'", i->pokemon->abilities[j]);

            if (strlen(i->pokemon->abilities[j + 1]) > 0) {
                printf(", ");
            }
        }

        printf("] - ");

        printf("%.1lfkg - %.1lfm - %d%% - %s - %d gen] - %02d/%02d/%d\n",
               i->pokemon->weight, i->pokemon->height, i->pokemon->captureRate,
               i->pokemon->isLegendary ? "true" : "false",
               i->pokemon->generation, i->pokemon->captureDate.dia,
               i->pokemon->captureDate.mes, i->pokemon->captureDate.ano);
    }
}

bool isEnd(char *input) {
    return (strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' &&
            input[2] == 'M');
}

int main() {
    Pokemon *pokemons = readCsv("../tmp/pokemon.csv");

    Queue queuePokemons = newQueue();

    char input[30];
    int id;

    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);
        insert(&queuePokemons, search(pokemons, id));
    }

    int operationsNumber = 0;

    Pokemon *deletedPokemons;
    int k = 0;

    scanf("%d", &operationsNumber);

    for (int j = 0; j < operationsNumber; j++) {
        char *operation = (char *)malloc(sizeof(char) * 3);
        scanf("%s", operation);

        if (strcmp(operation, "I") == 0) {
            int number;
            scanf("%d", &number);
            insert(&queuePokemons, search(pokemons, number));
        }

        if (strcmp(operation, "R") == 0) {
            deletedPokemons = removal(&queuePokemons);
            printf("(R) %s\n", deletedPokemons->name);
        }

        free(operation);
    }

    printf("\n");

    displayInformation(&queuePokemons);

    free(pokemons);

    return 0;
}