#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/**
 * TP03Q06 - Pilha com Alocação Flexível em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 07/11/2024
 */

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

Pokemon* readCsv(char fileName[]) {
    Pokemon* pokemons = (Pokemon*) malloc(801 * sizeof(Pokemon));

    if (!pokemons) {
        printf("Erro de alocação de memória.\n");
    }

    FILE* file = fopen(fileName, "r");

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

typedef struct Cell {
    Pokemon *pokemon;
    struct Cell *next;
} Cell;

Cell *newCell(Pokemon *pokemon) {
    Cell *temp = (Cell *) malloc(sizeof(Cell));
    temp->pokemon = pokemon;
    temp->next = NULL;
    return temp;
}

typedef struct Stack {
    struct Cell *top;
    int size;
} Stack;

Stack newStack(){
    Stack temp;
    temp.top = NULL;
    temp.size = 0;
    return temp;
}

void push(Stack *p, Pokemon *pokemon) {
    Cell *temp = newCell(pokemon);

    if (p->top == NULL) {
        p->top = temp;
    } else {
        Cell *current = p->top;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = temp;
    }

    p->size++;
}

Pokemon *pop(Stack *p) {
    if (p->top == NULL) {
        printf("\nA pilha está vázia.\n");
        return NULL;
    }

    Cell *current = p->top;
    Cell *previous = NULL;

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        p->top = NULL;
    } else {
        previous->next = NULL;
    }

    Pokemon *pokemon = current->pokemon;

    free(current);

    p->size--;

    return pokemon;
}

void showStack(Stack *l) {
    Cell *i;
    int count = 0;

    for (i = l->top; i != NULL; i = i->next) {
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
            i->pokemon->captureDate.day, 
            i->pokemon->captureDate.month, 
            i->pokemon->captureDate.year
        );
    }
}

bool isEnd(char *input) {
    return (strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' && input[2] == 'M');
}

int main() {
    Pokemon* pokemons = readCsv("../tmp/pokemon.csv");

    Stack StackPokemons = newStack();

    char input[30];
    int id;
    
    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);
        push( &StackPokemons, search(pokemons, id));
    }

    int operationsNumber = 0;

    Pokemon *deletedPokemons[50];
    int k = 0;

    scanf("%d", &operationsNumber);

    for (int j = 0; j < operationsNumber; j++) {
        char *operation = (char *) malloc (sizeof(char) * 3);
        scanf("%s", operation);

        if (strcmp(operation, "I") == 0) {
            int number;
            scanf("%d", &number);

            push(&StackPokemons, search(pokemons, number));
        }
        
        if (strcmp(operation, "R") == 0) {
            deletedPokemons[k++] = pop(&StackPokemons);
        }

        free(operation);
    }

    for (int i = 0; i < k; i++) {
        printf("(R) %s\n", deletedPokemons[i]->name);
    }

    showStack(&StackPokemons);

    free(pokemons);

    return 0;
}