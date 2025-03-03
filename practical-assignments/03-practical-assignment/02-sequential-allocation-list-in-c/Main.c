#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * TP03Q02 - Lista com Alocação Sequencial em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 30/10/2024
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

typedef struct List {
    Pokemon **pokemons;
    int number;
} List;

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
    char *str = (char*) malloc (11 * sizeof(char));
    sprintf(str, "%02d/%02d/%04d", date.day, date.month, date.year);
    return str;
}

int getId(Pokemon *p) {
    return p->id;
}

void setId(Pokemon *p, int id) {
    p->id = id;
}

int getGeneration(Pokemon *p) {
    return p->generation;
}

void setGeneration(Pokemon *p, int generation) {
    p->generation = generation;
}

char *getName(Pokemon *p) {
    return p->name;
}

void setName(Pokemon *p, char *name) {
    p->name = name;
}

char *getDescription(Pokemon *p) {
    return p->description;
}

void setDescription(Pokemon *p, char *description) {
    p->description = description;
}

char *getTypes(Pokemon *p, int index) {
    return p->types[index];
}

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

char *getAbilities(Pokemon *p, int index) {
    return p->abilities[index];
}

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

double getWeight(Pokemon *p) {
    return p->weight;
}

void setWeight(Pokemon *p, double weight) {
    p->weight = weight;
}

double getHeight(Pokemon *p) {
    return p->height;
}

void setHeight(Pokemon *p, double height) {
    p->height = height;
}

int getCaptureRate(Pokemon *p) {
    return p->captureRate;
}

void setCaptureRate(Pokemon *p, int captureRate) {
    p->captureRate = captureRate;
}

bool getIsLegendary(Pokemon *p) {
    return p->isLegendary;
}

void setIsLegendary(Pokemon *p, bool isLegendary) {
    p->isLegendary = isLegendary;
}

Date getCaptureDate(Pokemon *p) {
    return p->captureDate;
}

void setCaptureDate(Pokemon *p, Date captureDate) {
    p->captureDate = captureDate;
}

void setCaptureDateString(Pokemon *p, char *captureDate) {
    p->captureDate = stringToDate(captureDate);
}

Pokemon createPokemon(int id, int generation, char *name, char *description, char *type1, char *type2, char *abilities[6], double weight, double height, int captureRate, bool isLegendary, Date captureDate) {
    Pokemon pokemon;

    setId(&pokemon, id);
    setGeneration(&pokemon, generation);

    char *nameCopy = strdup(name);
    char *descriptionCopy = strdup(description);

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
    char *ptr = line;
    int inQuotes = 0;
    char *fieldStart = ptr;

    while (*ptr && fieldCount < max_fields) {
        if (*ptr == '"') {
            inQuotes = !inQuotes;
        } else if (*ptr == ',' && !inQuotes) {
            *ptr = '\0';
            fields[fieldCount++] = fieldStart;
            fieldStart = ptr + 1;
        }

        ptr++;
    }

    if (fieldCount < max_fields) {
        fields[fieldCount++] = fieldStart;
    }

    return fieldCount;
}

void readCsv(FILE *file, Pokemon *pokemons, int *n) {
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
        pokemon.name = strdup(fields[2]);
        pokemon.description = strdup(fields[3]);
        
        setTypes(&pokemon, 0, fields[4]);

        if (strlen(fields[5]) > 0) {
            setTypes(&pokemon, 1, fields[5]);
        } else {
            strcpy(pokemon.types[1], "");
        }

        char *abilitiesField = fields[6];

        if (abilitiesField[0] == '"' && abilitiesField[strlen(abilitiesField) - 1] == '"') {
            abilitiesField[strlen(abilitiesField) - 1] = '\0';
            abilitiesField++;
        }

        if (abilitiesField[0] == '[' && abilitiesField[strlen(abilitiesField) - 1] == ']') {
            abilitiesField[strlen(abilitiesField) - 1] = '\0';
            abilitiesField++;
        }

        char *abilityToken;
        char *restAbilities = abilitiesField;
        int abilityIndex = 0;

        while ((abilityToken = strtok_r(restAbilities, ",", &restAbilities)) && abilityIndex < 6) {
            while (*abilityToken == ' ' || *abilityToken == '\'') {
                abilityToken++;
            }

            char *tempEnd = abilityToken + strlen(abilityToken) - 1;

            while (tempEnd > abilityToken && (*tempEnd == ' ' || *tempEnd == '\'')) {
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
        
        pokemons[*n] = pokemon;
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

    printf("'] - ");

    int numberAbilities = getNumberAbilities(p);

    printf("[");

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

    free(data);

    printf("\n");
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

Pokemon *findPokemonById(Pokemon pokemons[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (pokemons[i].id == id) {
            return &pokemons[i];
        }
    }

    return NULL;
}

List initializeList(int quantity) {
    List list;

	list.pokemons = malloc (quantity * sizeof(Pokemon*));
	list.number = 0;

	return list;
}

void insert(List *list, Pokemon *pokemon, int position) {
    if (list->number >= 100 || position < 0 || position > list->number) {
        printf("Erro: Posição inválida ou lista cheia.\n");
    }

    for (int i = list->number; i > position; i--) {
        list->pokemons[i] = list->pokemons[i - 1];
    }

    list->pokemons[position] = pokemon;
    list->number++;
}

void insertStart(List *list, Pokemon *pokemon) {
    insert(list, pokemon, 0);
}

void insertEnd(List *list, Pokemon *pokemon) {
    insert(list, pokemon, list->number);
}

Pokemon *removal(List *list, int position) {
    if (list->number == 0 || position < 0 || position >= list->number) {
        printf("Erro: Posição inválida ou lista vazia.\n");
        exit(EXIT_FAILURE);
    }

    Pokemon *removedPokemon = list->pokemons[position];

    for (int i = position; i < list->number - 1; i++) {
        list->pokemons[i] = list->pokemons[i + 1];
    }

    list->number--;

    return removedPokemon;
}

Pokemon *removalStart(List *list) {
    return removal(list, 0);
}

Pokemon *removalEnd(List *list) {
    return removal(list, (list->number) - 1);
}

void printList(List *list) {
    for (int i = 0; i < list->number; i++) {
        printf("[%d] ", i);
        displayInformation(list->pokemons[i]);
    }
}

int main() {
    FILE *file = fopen("../tmp/pokemon.csv", "r");   

    if (file == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
    } 

    Pokemon pokemons[801];
    int n = 0;

    readCsv(file, pokemons, &n);

    fclose(file);

    List pokemonList = initializeList(100);

    char inputId[10];

    scanf("%s", inputId);
    
    while (strcmp(inputId, "FIM") != 0) {
        int id = atoi(inputId);
        Pokemon *p = findPokemonById(pokemons, n, id);

        if (p != NULL) {
            insertEnd(&pokemonList, p);
        }
        
        scanf("%s", inputId); 
    }

    int commandsQuantity;
    char commands[3];

    scanf("%i", &commandsQuantity);

    for (int i = 0; i < commandsQuantity; i++) {
        scanf("%s", commands);

        if (strcmp(commands, "II") == 0) {
            scanf("%s", inputId);

            int id = atoi(inputId);
            Pokemon *pokemon = findPokemonById(pokemons, n, id);

            if (pokemon != NULL) {
                insertStart(&pokemonList, pokemon);
            }
        } else if (strcmp(commands, "I*") == 0) {
            int position;

            scanf("%d", &position);
            scanf("%s", inputId); 

            int id = atoi(inputId);
            Pokemon *pokemon = findPokemonById(pokemons, n, id);

            if (pokemon != NULL) {
                insert(&pokemonList, pokemon, position);
            }
        } else if (strcmp(commands, "IF") == 0) {
            scanf("%s", inputId);

            int id = atoi(inputId);
            Pokemon *pokemon = findPokemonById(pokemons, n, id);

            if (pokemon != NULL) {
                insertEnd(&pokemonList, pokemon);
            }
        } else if (strcmp(commands, "RI") == 0) {
            Pokemon *pokemon = removalStart(&pokemonList);

            if (pokemon != NULL) {
                printf("(R) %s\n", pokemon->name);
            }
        } else if (strcmp(commands, "R*") == 0) {
            int position;

            scanf("%d", &position);

            Pokemon *pokemon = removal(&pokemonList, position);

            if (pokemon != NULL) {
                printf("(R) %s\n", pokemon->name);
            }
        } else if (strcmp(commands, "RF") == 0) {
            Pokemon *pokemon = removalEnd(&pokemonList);

            if (pokemon != NULL) {
                printf("(R) %s\n", pokemon->name);
            }
        }
    }

    printList(&pokemonList);
 
    for (int i = 0; i < n; i++) {
        free(pokemons[i].name);
        free(pokemons[i].description);
    }

    return 0;
}