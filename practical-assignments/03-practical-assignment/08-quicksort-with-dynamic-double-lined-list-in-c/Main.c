#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/**
 * TP03Q08 - Quicksort com LISTA DINÂMICA DUPLAMENTE ENCADEADA em C
 * 
 * @author Artur Bomtempo Colen
 * @version 2.0, 11/11/2024
 */

int comparisons = 0;
int movements = 0;

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

Pokemon *search(Pokemon* pokemons, int id) {
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
    Pokemon* pokemons = (Pokemon *) malloc(801 * sizeof(Pokemon));

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

void saveExecutionFile(const char *filename, long totalTime) {
    FILE *file = fopen(filename, "w+");

    if (file == NULL) {
        printf("Erro ao gerar o arquivo.\n");
    } else {
        fprintf(file, "847235\t%d\t%d\t%ldms", comparisons, movements, totalTime);
        
        fclose(file);
    }
}

typedef struct DoubleCell {
    Pokemon *pokemon;
    struct DoubleCell *next, *previous;
} DoubleCell;

DoubleCell *newDoubleCell(Pokemon *pokemon) {
    DoubleCell *temp = (DoubleCell *) malloc(sizeof(DoubleCell));
    temp->pokemon = pokemon;
    temp->previous = NULL;
    temp->next = NULL;
    return temp;
}

typedef struct DoubleList {
    struct DoubleCell *first, *last;
    int size;
} DoubleList;

DoubleList *newDoubleList() {
    DoubleList *temp = (DoubleList *) malloc(sizeof(DoubleList));
    temp->first = temp->last = newDoubleCell(NULL);
    temp->size = 0;
    return temp;
}

void insertStart(DoubleList *list, Pokemon *pokemon) {
    DoubleCell *temp = newDoubleCell(pokemon);
    temp->next = list->first;

    list->first->pokemon = pokemon;
    list->first->previous = temp; 
    list->first = temp;
    list->size++;
}

void insertEnd(DoubleList *list, Pokemon *pokemon) {
    list->last->next = newDoubleCell(pokemon);
    list->last->next->previous = list->last;
    list->last = list->last->next;
    list->size++;
}

Pokemon *removeEnd(DoubleList *list) {
    if (list->first == list->last) {
        printf("\nA lista está vazia.\n");
        return 0;
    }

    DoubleCell *temp = list->last;
    Pokemon *pokemon = temp->pokemon;

    list->last = list->last->previous;
    list->last->next = NULL;
    list->size--;

    free(temp);

    return pokemon;
}

Pokemon *removal(DoubleList *list, int position) {
    if (list->first == list->last) {
        printf("\nA lista está vazia.\n");
        return NULL;
    } else if (position < 0 || position > list->size - 1) {
        printf("Erro ao tentar remover item da posição (%d/ tamanho = %d) inválida.", position, list->size);
        return NULL;
    } else if (position == list->size - 1) {
        return removeEnd(list);
    } else {
        DoubleCell *previous = list->first;

        for (int i = 0; i < position; i++) {
            previous = previous->next;
        }

        DoubleCell *temp = previous->next;
        Pokemon *pokemon = temp->pokemon;

        previous->next = temp->next;

        free(temp);

        if (position == list->size - 1) {
            list->last = previous;
        }
        
        list->size--;

        return pokemon;
    }
}

void displayList(DoubleList *l) {
    DoubleCell *i;
    int count = 0;

    for (i = l->first->next; i != NULL; i = i->next) {
        printf("[#%d -> %s: %s - ", i->pokemon->id, i->pokemon->name, i->pokemon->description);
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
            i->pokemon->weight, 
            i->pokemon->height, 
            i->pokemon->captureRate, 
            i->pokemon->isLegendary ? "true" : "false", 
            i->pokemon->generation,
            i->pokemon->captureDate.dia, 
            i->pokemon->captureDate.mes, 
            i->pokemon->captureDate.ano
        );
    }
}

void deleteList(DoubleList *list) {
    while (list->size > 0) {
        removal(list,0);
    }

    free(list->first);
}

DoubleCell* getPivot(DoubleList *list, int position) {
    DoubleCell *current = list->first->next;

    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }

    return current;
}

void swap(DoubleList *list, DoubleCell *ci, DoubleCell *cj) {
    Pokemon *temp = ci->pokemon;
    ci->pokemon = cj->pokemon;
    cj->pokemon = temp;
}

void quickSort(DoubleList *list, int left, int right, DoubleCell *cLeft, DoubleCell *cRight) {
    DoubleCell *ci = cLeft, *cj = cRight;
    int i = left, j = right;
    DoubleCell *pivot = getPivot(list, left);

    while (i <= j) {
        while ((ci->pokemon->generation < pivot->pokemon->generation || (ci->pokemon->generation == pivot->pokemon->generation && strcmp(ci->pokemon->name, pivot->pokemon->name) < 0))) {
            comparisons++;
            i++;

            if (ci->next != NULL) {
                ci = ci->next;
            }
        }

        while ((cj->pokemon->generation > pivot->pokemon->generation || (cj->pokemon->generation == pivot->pokemon->generation && strcmp(cj->pokemon->name, pivot->pokemon->name) > 0))) {
            comparisons++;
            j--;

            if (cj->previous != NULL) {
                cj = cj->previous;
            }
        }

        if (i <= j) {
            movements += 3;

            swap(list, ci, cj);

            if (ci->next != NULL) {
                ci = ci->next;
            }

            i++;

            if (cj->previous != NULL) {
                cj = cj->previous;
            }

            j--;
        }
    }

    if (left < j) {
        quickSort(list, left, j, cLeft, cj);
    }

    if (i < right) {
        quickSort(list, i, right, ci, cRight);
    }
}

bool isEnd(char* input) {
    return (strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' && input[2] == 'M');
}

int main() {
    clock_t startClock, endClock;
    double totalTime;

    Pokemon* pokemons = readCsv("../tmp/pokemon.csv");

    DoubleList *pokemonsList = newDoubleList();

    char input[30];
    int id;
    
    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);
        insertEnd( pokemonsList, search(pokemons, id));
    }

    startClock = clock();

    quickSort(pokemonsList, 0, pokemonsList->size - 1, pokemonsList->first->next, pokemonsList->last);

    endClock = clock();

    displayList(pokemonsList);

    totalTime = ((double)(endClock - startClock));

    saveExecutionFile("847235_quicksort2.txt", totalTime);

    free(pokemons);

    deleteList(pokemonsList);

    return 0;
}