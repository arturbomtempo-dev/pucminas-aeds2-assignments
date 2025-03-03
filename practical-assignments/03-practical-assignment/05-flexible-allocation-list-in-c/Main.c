#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

/**
 * TP03Q05 - Lista com Alocação Flexível em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 05/11/2024
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

Pokemon *search(Pokemon* pokemons, int id) {
    Pokemon *pokemon;
    
    for (int i = 0; i < 801; i++) {
        if (pokemons[i].id == id) {
            pokemon = &pokemons[i];
        }
    }
    
    return pokemon; 
}

void removeOccurrences(char *str, char caractere) {
    int i, j = 0;
    size_t comprimento = strlen(str);
    
    for (i = 0; i < comprimento; i++) {
        if (str[i] != caractere) {
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
    Pokemon *pokemons = (Pokemon *)malloc (801 * sizeof(Pokemon));

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

        char *stringAbilities = removeAttribute(&token, ','); 

        removeOccurrences(stringAbilities, '[');
        removeOccurrences(stringAbilities, ']');
        removeOccurrences(stringAbilities, '\'');

        char *tokenAbilities = stringAbilities;
        int indexAbility = 0;

        while (*tokenAbilities != '\0' && indexAbility < 10) {
            while (isspace(*tokenAbilities)) {
                tokenAbilities++;
            }

            char *startAbility = tokenAbilities;
            char *endAbility;
            
            if (*startAbility == '\'') {
                startAbility++;
                endAbility = strchr(startAbility, '\'');
            } else {
                endAbility = strchr(startAbility, ','); 
            }

            if (endAbility != NULL) {
                *endAbility = '\0'; 
                strcpy(temp->abilities[indexAbility], startAbility);
                indexAbility++;
                tokenAbilities = endAbility + 1;
            } else {
                strcpy(temp->abilities[indexAbility], startAbility);
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

typedef struct List {
    struct Cell *first, *last;
    int size;
} List;

Cell *newCell(Pokemon *pokemon) {
    Cell *temp = (Cell *) malloc (sizeof(Cell));
    temp->pokemon = pokemon;
    temp->next = NULL;
    return temp;
}

List newList() {
    List temp;
    temp.first = temp.last = newCell(NULL);
    temp.size = 0;

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

void insert(List *list, Pokemon *pokemon, int position) {
    if (position < 0 || position > list->size) {
        printf("Erro ao tentar inserir na posição (%d/ tamanho = %d) inválida.", position, list->size);
    } else if (position == 0) {
        insertStart(list, pokemon);
    } else if (position == list->size) {
        insertEnd(list, pokemon);
    } else {
        Cell *previous = list->first;

        for (int i = 0; i < position; i++) {
            previous = previous->next;
        }

        Cell *temp = newCell(pokemon);
        temp->next = previous->next;
        previous->next = temp;
        list->size++;
    }
}

Pokemon *removal(List *list, int position) {
    if (list->first == list->last) {
        printf("\nA list está vazia!\n");
        return NULL;
    } else if (position < 0 || position >= list->size) {
        printf("Erro ao tentar remover item da posição (%d / tamanho = %d) inválida.\n", position, list->size);
        return NULL;
    } else {
        Cell *previous = list->first;

        for (int i = 0; i < position; i++) {
            previous = previous->next;
        }

        Cell *temp = previous->next;
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

Pokemon *removeStart(List *list) {
    return removal(list, 0);
}

Pokemon *removeEnd(List *list) {
    return removal(list, list->size-1);
}

void showList(List *list) {
    Cell *i;
    int count = 0;

    for (i = list->first->next; i != NULL; i = i->next) {
        printf("[%d] ", count++);
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
            i->pokemon->captureDate.ano);
    }
}

bool isEnd(char *input) {
    return (strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' && input[2] == 'M');
}

int main() {
    Pokemon* pokemons = readCsv("../tmp/pokemon.csv");

    List pokemonsList = newList();

    char input[30];
    int id;
    
    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);

        insertEnd(&pokemonsList, search(pokemons, id));
    }

    int numberOperations = 0;

    Pokemon *deletedPokemons[50];
    int k = 0;

    scanf("%d", &numberOperations);

    for (int j = 0; j < numberOperations; j++) {
        char* operation = (char *) malloc(sizeof(char) * 3);
        scanf("%s", operation);

        if (strcmp(operation, "II") == 0) {
            int number;
            scanf("%d", &number);
            insertStart(&pokemonsList, search(pokemons, number));
        }
            
        if (strcmp(operation, "IF") == 0) {
            int number;
            scanf("%d", &number);
            insertEnd(&pokemonsList, search(pokemons, number));
        }
            
        if (strcmp(operation, "RI") == 0) {
            deletedPokemons[k++] = removeStart(&pokemonsList);
        }
            
        if (strcmp(operation, "RF") == 0) {
            deletedPokemons[k++] = removeEnd(&pokemonsList);
        }
            
        if (strcmp(operation, "I*") == 0) {
            int position;
            scanf("%d", &position);
            int number;
            scanf("%d", &number);
            insert(&pokemonsList, search(pokemons, number), position);
        }
            
        if (strcmp(operation, "R*") == 0) {
            int position;
            scanf("%d", &position);
            deletedPokemons[k++] = removal(&pokemonsList, position);
        }

        free(operation);
    }

    for (int i = 0; i < k; i++) {
        printf("(R) %s\n", deletedPokemons[i]->name);
    }

    showList(&pokemonsList);

    free(pokemons);

    return 0;
}