#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * TP02Q16 - Ordenação PARCIAL por Inserção
 *
 * @author Artur Bomtempo Colen
 * @version 2.0, 15/10/2024
 */

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef struct Pokemon {
    int id;
    int generation;
    char *name;
    char *description;
    char types[2][50];
    char abilities[6][50];
    double weight;
    double height;
    int captureRate;
    bool isLegendary;
    Date captureDate;
} Pokemon;

Date stringToDate(char *str) {
    Date date;

    if (str != NULL && strlen(str) > 0) {
        sscanf(str, "%d/%d/%d", &date.day, &date.month, &date.year);
    } else {
        date.day = 0;
        date.month = 0;
        date.year = 0;
    }

    return date;
}

char *dateToString(Date date) {
    char *str = (char *)malloc(11 * sizeof(char));

    sprintf(str, "%02d/%02d/%04d", date.day, date.month, date.year);

    return str;
}

char *strdupFunction(const char *s) {
    char *copy = (char *)malloc(strlen(s) + 1);

    if (copy != NULL) {
        strcpy(copy, s);
    }

    return copy;
}

int getId(Pokemon *p) { return p->id; }

void setId(Pokemon *p, int id) { p->id = id; }

int getGeneration(Pokemon *p) { return p->generation; }

void setGeneration(Pokemon *p, int generation) { p->generation = generation; }

char *getName(Pokemon *p) { return p->name; }

void setName(Pokemon *p, char *name) { p->name = name; }

char *getDescription(Pokemon *p) { return p->description; }

void setDescription(Pokemon *p, char *description) {
    p->description = description;
}

char *getTypes(Pokemon *p, int index) { return p->types[index]; }

int getNumberTypes(Pokemon *p) {
    int count = 0;

    for (int i = 0; i < 2; i++) {
        if (strlen(p->types[i]) > 0) {
            count++;
        }
    }

    return count;
}

void setTypes(Pokemon *p, int index, char *type) {
    strncpy(p->types[index], type, sizeof(p->types[index]) - 1);
    p->types[index][sizeof(p->types[index]) - 1] = '\0';
}

char *getAbilities(Pokemon *p, int index) { return p->abilities[index]; }

int getNumberAbilities(Pokemon *p) {
    int count = 0;

    for (int i = 0; i < 6; i++) {
        if (strlen(p->abilities[i]) > 0) {
            count++;
        }
    }

    return count;
}

void setAbilities(Pokemon *p, int index, const char *ability) {
    strncpy(p->abilities[index], ability, sizeof(p->abilities[index]) - 1);
    p->abilities[index][sizeof(p->abilities[index]) - 1] = '\0';
}

double getWeight(Pokemon *p) { return p->weight; }

void setWeight(Pokemon *p, double weight) { p->weight = weight; }

double getHeight(Pokemon *p) { return p->height; }

void setHeight(Pokemon *p, double height) { p->height = height; }

int getCaptureRate(Pokemon *p) { return p->captureRate; }

void setCaptureRate(Pokemon *p, int captureRate) {
    p->captureRate = captureRate;
}

bool getIsLegendary(Pokemon *p) { return p->isLegendary; }

void setIsLegendary(Pokemon *p, bool isLegendary) {
    p->isLegendary = isLegendary;
}

Date getCaptureDate(Pokemon *p) { return p->captureDate; }

void setCaptureDate(Pokemon *p, Date captureDate) {
    p->captureDate = captureDate;
}

void setCaptureDateString(Pokemon *p, char *captureDate) {
    p->captureDate = stringToDate(captureDate);
}

Pokemon createPokemon(int id, int generation, char *name, char *description,
                      char *type1, char *type2, char *abilities[6],
                      double weight, double height, int captureRate,
                      bool isLegendary, Date captureDate) {
    Pokemon pokemon;

    setId(&pokemon, id);
    setGeneration(&pokemon, generation);

    char *nameCopy = strdupFunction(name);
    char *descriptionCopy = strdupFunction(description);

    setName(&pokemon, nameCopy);
    setDescription(&pokemon, descriptionCopy);
    setTypes(&pokemon, 0, type1);

    if (type2 != NULL) {
        setTypes(&pokemon, 1, type2);
    }

    for (int i = 0; i < 6; i++) {
        if (abilities[i] != NULL) {
            setAbilities(&pokemon, i, abilities[i]);
        } else {
            strcpy(pokemon.abilities[i], "");
        }
    }

    setWeight(&pokemon, weight);
    setHeight(&pokemon, height);
    setCaptureRate(&pokemon, captureRate);
    setIsLegendary(&pokemon, isLegendary);
    setCaptureDate(&pokemon, captureDate);

    return pokemon;
}

int splitCsvLine(char *line, char **fields, int max_fields) {
    int fieldCount = 0;
    char *pointer = line;
    int inQuotes = 0;
    char *fieldStart = pointer;

    while (*pointer && fieldCount < max_fields) {
        if (*pointer == '"') {
            inQuotes = !inQuotes;
        } else if (*pointer == ',' && !inQuotes) {
            *pointer = '\0';
            fields[fieldCount++] = fieldStart;
            fieldStart = pointer + 1;
        }

        pointer++;
    }

    if (fieldCount < max_fields) {
        fields[fieldCount++] = fieldStart;
    }

    return fieldCount;
}

void readCsv(FILE *file, Pokemon *pokedex, int *n) {
    char line[1024];

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        Pokemon pokemon;

        memset(&pokemon, 0, sizeof(Pokemon));

        char *fields[12];
        int fieldCount = splitCsvLine(line, fields, 12);

        pokemon.id = atoi(fields[0]);
        pokemon.generation = atoi(fields[1]);
        pokemon.name = strdupFunction(fields[2]);
        pokemon.description = strdupFunction(fields[3]);

        setTypes(&pokemon, 0, fields[4]);

        if (strlen(fields[5]) > 0) {
            setTypes(&pokemon, 1, fields[5]);
        } else {
            strcpy(pokemon.types[1], "");
        }

        char *abilitiesField = fields[6];

        if (abilitiesField[0] == '"' &&
            abilitiesField[strlen(abilitiesField) - 1] == '"') {
            abilitiesField[strlen(abilitiesField) - 1] = '\0';
            abilitiesField++;
        }
        if (abilitiesField[0] == '[' &&
            abilitiesField[strlen(abilitiesField) - 1] == ']') {
            abilitiesField[strlen(abilitiesField) - 1] = '\0';
            abilitiesField++;
        }

        char *abilityToken;
        char *restAbilities = abilitiesField;
        int abilityIndex = 0;

        while ((abilityToken = strtok_r(restAbilities, ",", &restAbilities)) &&
               abilityIndex < 6) {
            while (*abilityToken == ' ' || *abilityToken == '\'') {
                abilityToken++;
            }

            char *tempEnd = abilityToken + strlen(abilityToken) - 1;

            while (tempEnd > abilityToken &&
                   (*tempEnd == ' ' || *tempEnd == '\'')) {
                *tempEnd = '\0';
                tempEnd--;
            }

            if (strlen(abilityToken) > 0) {
                setAbilities(&pokemon, abilityIndex, abilityToken);
                abilityIndex++;
            }
        }

        for (; abilityIndex < 6; abilityIndex++) {
            strcpy(pokemon.abilities[abilityIndex], "");
        }

        pokemon.weight = atof(fields[7]);
        pokemon.height = atof(fields[8]);
        pokemon.captureRate = atoi(fields[9]);
        pokemon.isLegendary = atoi(fields[10]);
        pokemon.captureDate = stringToDate(fields[11]);

        pokedex[*n] = pokemon;
        (*n)++;
    }
}

void displayInformation(Pokemon *p) {
    printf("[#%d -> %s: %s - ['", getId(p), getName(p), getDescription(p));

    int numberTypes = getNumberTypes(p);

    if (numberTypes > 0) {
        printf("%s", getTypes(p, 0));
    }

    if (numberTypes > 1) {
        printf("', '%s", getTypes(p, 1));
    }

    printf("'] - [");

    int numberAbilities = getNumberAbilities(p);

    for (int i = 0; i < numberAbilities; i++) {
        printf("'%s'", getAbilities(p, i));

        if (i < numberAbilities - 1) {
            printf(", ");
        }
    }

    printf("] - ");

    printf("%.1fkg - ", getWeight(p));
    printf("%.1fm - ", getHeight(p));
    printf("%d%% - ", getCaptureRate(p));
    printf("%s - ", getIsLegendary(p) ? "true" : "false");
    printf("%d gen] - ", getGeneration(p));

    char *data = dateToString(getCaptureDate(p));

    printf("%s", data);

    printf("\n");

    free(data);
}

int compareDates(Date *date1, Date *date2) {
    if (date1->year != date2->year) {
        return date1->year - date2->year;
    }

    if (date1->month != date2->month) {
        return date1->month - date2->month;
    }

    return date1->day - date2->day;
}

void swap(Pokemon *a, Pokemon *b) {
    Pokemon aux = *a;

    *a = *b;
    *b = aux;
}

void partialInsertionSort(Pokemon findPokemon[], int size, int k,
                          int *comparisons, int *movements) {
    for (int i = 1; i < size; i++) {
        Pokemon key = findPokemon[i];
        int j = i - 1;

        while (j >= 0) {
            int date =
                compareDates(&key.captureDate, &findPokemon[j].captureDate);
            int name = strcmp(key.name, findPokemon[j].name);

            (*comparisons)++;

            if (date < 0 || ((date == 0) && (name < 0))) {
                findPokemon[j + 1] = findPokemon[j];

                (*movements)++;

                j = j - 1;
            } else {
                break;
            }
        }

        (*movements)++;
        findPokemon[j + 1] = key;
    }
}

int main() {
    clock_t start = clock();

    FILE *file = fopen("../tmp/pokemon.csv", "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return 1;
    }

    Pokemon pokedex[801];
    int n = 0;

    readCsv(file, pokedex, &n);

    fclose(file);

    char inputId[10];
    scanf("%s", inputId);

    Pokemon findPokemon[51];
    int comparisons = 0;
    int movements = 0;
    int j = 0;

    while (strcmp(inputId, "FIM") != 0) {
        int id = atoi(inputId);

        for (int i = 0; i < n; i++) {
            if (pokedex[i].id == id) {
                findPokemon[j++] = pokedex[i];
                break;
            }
        }

        scanf("%s", inputId);
    }

    int k = 10;

    partialInsertionSort(findPokemon, j, k, &comparisons, &movements);

    for (int i = 0; i < k; i++) {
        displayInformation(&findPokemon[i]);
    }

    clock_t end = clock();
    double executionTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

    FILE *archive = fopen("847235_partialInsertionSort.txt", "w");

    if (archive == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(archive, "847235\t%d\t%d\t%.2f\n", comparisons, movements,
            executionTime);

    fclose(archive);

    for (int i = 0; i < n; i++) {
        free(pokedex[i].name);
        free(pokedex[i].description);
    }

    return 0;
}