#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/**
 * TP02Q10 - Quicksort
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 11/10/2024
 */

struct Date {
    int day;
    int month;
    int year;
} typedef Date;

struct Pokemon {
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
} typedef Pokemon;

Pokemon *searchPokemon(Pokemon *pokemons, int id) {
    Pokemon *pokemon;

    for (int i = 0; i < 801; i++) {
        if (pokemons[i].id == id) {
            pokemon = &pokemons[i];
        }
    }
    
    return pokemon; 
}

void removeOccurrences(char *str, char value) {
    int i, j = 0;
    size_t length = strlen(str);
    
    for (i = 0; i < length; i++) {
        if (str[i] != value) {
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
    Pokemon *pokemons = (Pokemon*) malloc(801 * sizeof(Pokemon));

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

        char *abilities = removeAttribute(&token, ','); 

        removeOccurrences(abilities, '[');
        removeOccurrences(abilities, ']');
        removeOccurrences(abilities, '\'');

        char *tokenAbilities = abilities;
        int abilityIndex = 0;

        while (*tokenAbilities != '\0' && abilityIndex < 10) {
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
                strcpy(temp->abilities[abilityIndex], startAbility);
                abilityIndex++;
                tokenAbilities = endAbility + 1;
            } else {
                strcpy(temp->abilities[abilityIndex], startAbility);
                tokenAbilities += strlen(startAbility);
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

void displayInformation(Pokemon *pokemon) {
    printf("[#%d -> %s: %s - ", pokemon->id, pokemon->name, pokemon->description);

    printf("['%s'", pokemon->type[0]);

    if (strlen(pokemon->type[1]) > 0) {
        printf(", '%s'", pokemon->type[1]);
    }

    printf("] - [");

    for (int i = 0; strlen(pokemon->abilities[i]) > 0; i++) {
        printf("'%s'", pokemon->abilities[i]);

        if (strlen(pokemon->abilities[i + 1]) > 0) {
            printf(", ");
        }
    }

    printf("] - ");

    printf("%.1lfkg - %.1lfm - %d%% - %s - %d gen] - %02d/%02d/%d\n", 
           pokemon->weight, 
           pokemon->height, 
           pokemon->captureRate, 
           pokemon->isLegendary ? "true" : "false", 
           pokemon->generation,
           pokemon->captureDate.day, 
           pokemon->captureDate.month, 
           pokemon->captureDate.year);
}

void saveExecutionFile(const char *fileName, int comparisons, int movements, long totalTime) {
    FILE *file = fopen(fileName, "w+");

    if (file == NULL) {
        printf("Erro ao gerar o arquivo.\n");
    } else {
        fprintf(file, "847235\t%d\t%d\t%ldms", comparisons, movements, totalTime);
        fclose(file);
    }
}

int partition(Pokemon **pokemon, int low, int high, int *comparisons, int *movements) {
    Pokemon *pivot = pokemon[high]; 
    int i = low - 1; 

    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;

        if (pokemon[j]->generation < pivot->generation || (pokemon[j]->generation == pivot->generation && strcmp(pokemon[j]->name, pivot->name) < 0)) {
            i++;

            Pokemon *temp = pokemon[i];
            pokemon[i] = pokemon[j];
            pokemon[j] = temp;

            (*movements) += 2; 
        }
    }

    Pokemon *temp = pokemon[i + 1];
    pokemon[i + 1] = pokemon[high];
    pokemon[high] = temp;
    (*movements) += 2;

    return i + 1; 
}

void quickSort(Pokemon **pokemon, int low, int high, int *comparisons, int *movements) {
    if (low < high) {
        int pi = partition(pokemon, low, high, comparisons, movements);

        quickSort(pokemon, low, pi - 1, comparisons, movements);
        quickSort(pokemon, pi + 1, high, comparisons, movements);
    }
}

int main() {
    clock_t start, end;
    double totalTime;
    int comparisons = 0, movements = 0;

    Pokemon* pokemons = readCsv("../tmp/pokemon.csv");
    
    if (!pokemons) {
        printf("Pokemons nao inicializados.\n");
        return 1;
    }

    Pokemon *foundPokemons[200];

    char input[30];
    int id;
    int i = 0;
    
    while (scanf("%s", input) && strcmp(input, "FIM") != 0) {
        sscanf(input, "%d", &id);
        foundPokemons[i++] = searchPokemon(pokemons, id);
    }

    start = clock();
    quickSort(foundPokemons, 0, i - 1, &comparisons, &movements);
    end = clock();

    for (int j = 0; j < i; j++) {
        displayInformation(foundPokemons[j]);
    }

    totalTime = ((double)(end - start));

    saveExecutionFile("847235_quicksort.txt", comparisons, movements, totalTime);

    free(pokemons);

    return 0;
}