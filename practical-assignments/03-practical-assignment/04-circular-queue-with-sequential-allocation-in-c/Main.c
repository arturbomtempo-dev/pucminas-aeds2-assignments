#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

/**
 * TP03Q04 - Fila Circular com Alocação Sequencial em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 04/11/2024
 */

#define true 1
#define false 0

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

Pokemon *search(Pokemon* pokemons, int id) {
    Pokemon *pokemon;
    
    for (int i = 0; i < 801; i++) {
        if (pokemons[i].id == id) {
            pokemon = &pokemons[i];
        }
    }
    
    return pokemon; 
}

void removeOccurrences(char *str, char characters) {
    int i, j = 0;
    size_t length = strlen(str);
    
    for (i = 0; i < length; i++) {
        if (str[i] != characters) {
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
    Pokemon *pokemons = (Pokemon*) malloc (801 * sizeof(Pokemon));

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

        char *tokenAbilities = abilitiesString;
        int indexAbilities = 0;

        while (*tokenAbilities != '\0' && indexAbilities < 10) {
            while (isspace(*tokenAbilities)) {
                tokenAbilities++;
            }

            char *startAbilities = tokenAbilities;
            char *endAbilities;
            
            if (*startAbilities == '\'') {
                startAbilities++;
                endAbilities = strchr(startAbilities, '\'');
            } else {
                endAbilities = strchr(startAbilities, ','); 
            }

            if (endAbilities != NULL) {
                *endAbilities = '\0'; 
                strcpy(temp->abilities[indexAbilities], startAbilities);
                indexAbilities++;
                tokenAbilities = endAbilities + 1;
            } else {
                strcpy(temp->abilities[indexAbilities], startAbilities);
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

Pokemon *array[6 + 1];
int first, last;

void start() {
   first = 0;
   last = 0;
}

Pokemon *removal() {
    if (first == last) {
        printf("Erro ao remover.");
        exit(1);
    }
    
    Pokemon *temp = array[first];
    first = (first + 1) % 6;
    return temp;
}

void insert(Pokemon *x) {
    if (((last + 1) % 6) == first) {
        removal();
    }

    array[last] = x;
    last = (last + 1) % 6;
    
    int i = first;
    int sum = 0;
    int k = 0;

    while (i != last) {
        sum += array[i]->captureRate;
        i = ((i + 1) % 6);
        k++;
    }
        
    if (k > 0) {
        int roundedAverage = (int) round((double) sum / k);
        printf("Média: %d\n", roundedAverage);
    }
}

void displayInformation() {
   int i = first;
   int k = 0;

   printf("\n");

   while (i != last) {
        printf("[%d] ", k++);
        printf("[#%d -> %s: %s - ", array[i]->id, array[i]->name, array[i]->description);

        printf("['%s'", array[i]->type[0]);

        if (strlen(array[i]->type[1]) > 0) {
            printf(", '%s'", array[i]->type[1]);
        }

        printf("] - [");

        for (int j = 0; strlen(array[i]->abilities[j]) > 0; j++) {
            printf("'%s'", array[i]->abilities[j]);

            if (strlen(array[i]->abilities[j + 1]) > 0) {
                printf(", ");
            }
        }

        printf("] - ");

        printf("%.1lfkg - %.1lfm - %d%% - %s - %d gen] - %02d/%02d/%d\n", 
            array[i]->weight, 
            array[i]->height, 
            array[i]->captureRate, 
            array[i]->isLegendary ? "true" : "false", 
            array[i]->generation,
            array[i]->captureDate.day, 
            array[i]->captureDate.month, 
            array[i]->captureDate.year);

        i = ((i + 1) % 6);
   }
}

bool isEnd(char *input) {
    return (strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' && input[2] == 'M');
}

int main() {
    start();

    Pokemon *pokemons = readCsv("../tmp/pokemon.csv");

    char input[30];
    int id;
    
    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);

        insert(search(pokemons, id));
    }

    int numberOperations = 0;
    Pokemon *excludedPokemon;
    int k = 0;

    scanf("%d", &numberOperations);

    for (int j = 0; j < numberOperations; j++) {
        char *operation = (char *) malloc(sizeof (char) * 3);
        scanf("%s", operation);

        if (strcmp(operation, "I") == 0) {
            int number;
            scanf("%d", &number);
            insert(search(pokemons, number));
        }
            
        if (strcmp(operation, "R") == 0) {
            excludedPokemon = removal();
            printf("(R) %s\n", excludedPokemon->name);
        }

        free(operation);
    }

    displayInformation();

    free(pokemons);

    return 0;
}