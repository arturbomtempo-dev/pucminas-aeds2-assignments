#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * TP02Q08 - Shellsort
 *
 * @author Artur Bomtempo Colen
 * @version 1.0, 10/10/2024
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
    printf("[#%d -> %s: %s - ", pokemon->id, pokemon->name,
           pokemon->description);

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
           pokemon->weight, pokemon->height, pokemon->captureRate,
           pokemon->isLegendary ? "true" : "false", pokemon->generation,
           pokemon->captureDate.day, pokemon->captureDate.month,
           pokemon->captureDate.year);
}

void saveExecutionFile(const char *fileName, int comparisons, int movements,
                       long totalTime) {
    FILE *file = fopen(fileName, "w+");

    if (file == NULL) {
        printf("Erro ao gerar o arquivo.\n");
    } else {
        fprintf(file, "847235\t%d\t%d\t%ldms", comparisons, movements,
                totalTime);
        fclose(file);
    }
}

void colorInsertion(Pokemon **pokemon, int n, int color, int h,
                    int *comparisons, int *movements) {
    for (int i = (h + color); i < n; i += h) {
        Pokemon *tmp = pokemon[i];
        int j = i - h;

        (*comparisons) += 2;

        while ((j >= 0) && ((pokemon[j]->weight > tmp->weight) ||
                            ((pokemon[j]->weight == tmp->weight) &&
                             (strcmp(pokemon[j]->name, tmp->name) > 0)))) {
            (*movements)++;
            pokemon[j + h] = pokemon[j];
            j -= h;
        }

        (*movements)++;
        pokemon[j + h] = tmp;
    }
}

void shellSort(Pokemon **pokemon, int n, int *comparisons, int *movements) {
    int h = 1;

    do {
        h = (h * 3) + 1;
    } while (h < n);

    do {
        h /= 3;

        for (int color = 0; color < h; color++) {
            colorInsertion(pokemon, n, color, h, comparisons, movements);
        }
    } while (h != 1);
}

int main() {
    clock_t start, end;
    double totalTime;
    int comparisons = 0, movements = 0;

    Pokemon *pokemons = readCsv("../tmp/pokemon.csv");

    if (!pokemons) {
        printf("Pokemons não inicializados.\n");
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
    shellSort(foundPokemons, i, &comparisons, &movements);
    end = clock();

    for (int j = 0; j < i; j++) {
        displayInformation(foundPokemons[j]);
    }

    totalTime = ((double)(end - start));

    saveExecutionFile("847235_shellsort.txt", comparisons, movements,
                      totalTime);

    free(pokemons);

    return 0;
}