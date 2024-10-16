#include <sys/time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

/**
 * TP02Q14 - Radixsort
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 15/10/2024
 */

/**
 * Estrutura que representa um Pokémon com seus atributos principais.
 */
struct Pokemon {
    char id[256];
    int generation;
    char name[256];
    char description[256];
    char types[3][256];
    char abilities[6][256];
    double weight;
    double height;
    int captureRate;
    bool isLegendary;
    struct tm captureDate;
} typedef Pokemon;

/**
 * Retorna o ID do Pokémon.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @return ID do Pokémon como uma string.
 */
const char* getId(Pokemon *pokemon) {
    return pokemon->id;
}

/**
 * Retorna o nome do Pokémon.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @return Nome do Pokémon como uma string.
 */
const char* getName(Pokemon *pokemon) {
    return pokemon->name;
}

/**
 * Retorna a descrição do Pokémon.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @return Descrição do Pokémon como uma string.
 */
const char* getDescription(Pokemon *pokemon)  {
    return pokemon->description;
}

/**
 * Retorna o tipo do Pokémon no índice fornecido.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @param index Índice do tipo (0 a 2).
 * @return Tipo do Pokémon no índice especificado, ou uma string vazia se o índice for inválido.
 */
const char* getType(Pokemon *pokemon, int index) {
    if (index >= 0 && index < 3) {
        return pokemon->types[index];
    }

    return "";
}

/**
 * Retorna a habilidade do Pokémon no índice fornecido.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @param index Índice da habilidade (0 a 5).
 * @return Habilidade do Pokémon no índice especificado, ou uma string vazia se o índice for inválido.
 */
const char* getAbility(Pokemon *pokemon, int index) {
    if (index >= 0 && index < 6) {
        return pokemon->abilities[index];
    }

    return "";
}

/**
 * Retorna o peso do Pokémon.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @return Peso do Pokémon em quilogramas.
 */
double getWeight(Pokemon *pokemon) {
    return pokemon->weight;
}

/**
 * Retorna a altura do Pokémon.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @return Altura do Pokémon em metros.
 */
double getHeight(Pokemon *pokemon) {
    return pokemon->height;
}

/**
 * Verifica se o Pokémon é lendário.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @return `true` se o Pokémon for lendário, `false` caso contrário.
 */
bool getIsLegendary(Pokemon *pokemon) {
    return pokemon->isLegendary;
}

/**
 * Retorna a geração do Pokémon.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @return Geração do Pokémon.
 */
int getGeneration(Pokemon *pokemon) {
    return pokemon->generation;
}

/**
 * Retorna a taxa de captura do Pokémon.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @return Taxa de captura do Pokémon.
 */
int getCaptureRate(Pokemon *pokemon) {
    return pokemon->captureRate;
}

/**
 * Retorna a data de captura do Pokémon.
 *
 * @param pokemon Ponteiro para o Pokémon.
 * @return Estrutura `tm` representando a data de captura do Pokémon.
 */
struct tm getCaptureDate(Pokemon *pokemon) {
    return pokemon->captureDate;
}

/**
 * Converte uma string de data no formato "DD/MM/AAAA" em uma estrutura `tm`.
 *
 * @param dateString String que contém a data no formato "DD/MM/AAAA".
 * @param date Ponteiro para a estrutura `tm` onde a data será armazenada.
 */
void parseDate(char *dateString, struct tm *date) {
    if (sscanf(dateString, "%d/%d/%d", &date->tm_mday, &date->tm_mon, &date->tm_year) != 3) {
        return;
    }

    date->tm_mon -= 1;
    date->tm_year -= 1900;
}

/**
 * Divide uma linha CSV em campos separados e armazena os ponteiros para esses campos.
 *
 * @param line String contendo a linha CSV a ser dividida.
 * @param fields Array de strings onde os campos resultantes serão armazenados.
 * @param maximumFields Número máximo de campos a serem extraídos.
 * @return O número de campos extraídos.
 */
int splitCsvLine(char *line, char **fields, int maximumFields) {
    int fieldCount = 0;
    char *pointer = line;
    int inQuotes = 0;
    char *startField = pointer;

    while (*pointer && fieldCount < maximumFields) {
        if (*pointer == '"') {
            inQuotes = !inQuotes;
        } else if (*pointer == ',' && !inQuotes) {
            *pointer = '\0';
            fields[fieldCount++] = startField;
            startField = pointer + 1;
        }

        pointer++;
    }
    
    if (fieldCount < maximumFields) {
        fields[fieldCount++] = startField;
    }

    return fieldCount;
}

/**
 * Lê os dados de um arquivo CSV e preenche um array de Pokémon.
 *
 * @param file Ponteiro para o arquivo CSV a ser lido.
 * @param pokedex Array de struct `Pokemon` onde os dados do CSV serão armazenados.
 * @param n Ponteiro para um inteiro que indica o número de Pokémon lidos.
 */
void readCsv(FILE *file, Pokemon *pokedex, int *n) {
    char line[1024];

    fgets(line, sizeof(line), file); 

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; 

        Pokemon pokemon;
        memset(&pokemon, 0, sizeof(Pokemon)); 

        char *fields[12]; 
        int fieldCount = splitCsvLine(line, fields, 12);

        strncpy(pokemon.id, fields[0], 256);

        pokemon.generation = atoi(fields[1]);

        strncpy(pokemon.name, fields[2], 256);
        strncpy(pokemon.description, fields[3], 256);
        strncpy(pokemon.types[0], fields[4], 256);

        if (strlen(fields[5]) > 0) {
            strncpy(pokemon.types[1], fields[5], 256);
        }
        
        char *abilitiesField = fields[6];

        if (abilitiesField[0] == '"' && abilitiesField[strlen(abilitiesField) - 1] == '"') {
            abilitiesField[strlen(abilitiesField) - 1] = '\0';
            abilitiesField++;
        }
        
        if (abilitiesField[0] == '[' && abilitiesField[strlen(abilitiesField) - 1] == ']') 
        {
            abilitiesField[strlen(abilitiesField) - 1] = '\0';
            abilitiesField++;
        }

        char *abilityToken;
        char *restAbilities = abilitiesField;
        int abilityIndex = 0;

        while ((abilityToken = strtok(restAbilities, ",")) && abilityIndex < 6) {
            while (*abilityToken == ' ' || *abilityToken == '\'') {
                abilityToken++;
            }

            char *tempEnd = abilityToken + strlen(abilityToken) - 1;

            while (tempEnd > abilityToken && (*tempEnd == ' ' || *tempEnd == '\'')) {
                *tempEnd = '\0';
                tempEnd--;
            }

            if (strlen(abilityToken) > 0 && abilityIndex < 6) {
                strncpy(pokemon.abilities[abilityIndex], abilityToken, 256);
                abilityIndex++;
            }

            restAbilities = NULL;
        }

        pokemon.weight = atof(fields[7]);
        pokemon.height = atof(fields[8]);
        pokemon.captureRate = atoi(fields[9]);
        pokemon.isLegendary = atoi(fields[10]);

        struct tm captureDate = {0};

        parseDate(fields[11], &captureDate);
        pokemon.captureDate = captureDate;

        pokedex[*n] = pokemon;
        (*n)++;
    }
}

/**
 * Exibe as informações de um Pokémon em um formato estruturado.
 *
 * @param pokemon Ponteiro para o struct `Pokemon` cujas informações serão exibidas.
 */
void displayInformation(Pokemon* pokemon) {
    char dateString[11];

    strftime(dateString, sizeof(dateString), "%d/%m/%Y", &pokemon->captureDate);

    printf("[#%s -> %s: %s - [", getId(pokemon), getName(pokemon), getDescription(pokemon));

    for (int j = 0; j < 3 && strlen(getType(pokemon, j)) > 0; j++) {
        if (j > 0) {
            printf(", ");
        }

        printf("'%s'", getType(pokemon, j));
    }

    printf("] - [");

    for (int j = 0; j < 6 && strlen(getAbility(pokemon, j)) > 0; j++) {
        if (j > 0) {
            printf(", ");
        }

        printf("'%s'", getAbility(pokemon, j));
    }

    printf("] - ");

    printf("%.1fkg - %.1fm - %d%% - %s - %d gen] - %s\n", getWeight(pokemon), getHeight(pokemon), getCaptureRate(pokemon), getIsLegendary(pokemon) ? "true" : "false", getGeneration(pokemon), dateString);
}

long long now() {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);  
}

int quantityComparisons = 0;
int quantityMovements = 0;

/**
 * Retorna o comprimento máximo da primeira habilidade entre os Pokémon em um array.
 *
 * @param array Ponteiro para o array de Pokémon.
 * @param n O número de Pokémon no array.
 * @return O comprimento da string da habilidade mais longa.
 */
int getMaximumLength(Pokemon *array, int n) {
    int maximumLength = strlen(array[0].abilities[0]);

    for (int i = 1; i < n; i++) {
        int length = strlen(array[i].abilities[0]);

        quantityComparisons++;

        if (length > maximumLength) {
            maximumLength = length;
            quantityMovements++;
        }
    }

    return maximumLength;
}

/**
 * Ordena os Pokémon com base em um caractere específico de sua primeira habilidade usando Counting Sort.
 *
 * @param array Ponteiro para o array de Pokémon.
 * @param n O número de Pokémon no array.
 * @param charIndex O índice do caractere na habilidade a ser usado como chave para ordenação.
 */
void countSortByChar(Pokemon *array, int n, int charIndex) {
    Pokemon output[n];
    int count[256] = { 0 };

    for (int i = 0; i < n; i++) {
        char c = charIndex < strlen(array[i].abilities[0]) ? array[i].abilities[0][charIndex] : 0;

        count[(int)c]++;
        quantityMovements++;
    }

    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
        quantityMovements++;
    }

    for (int i = n - 1; i >= 0; i--) {
        char c = charIndex < strlen(array[i].abilities[0]) ? array[i].abilities[0][charIndex] : 0;

        output[count[(int)c] - 1] = array[i];
        count[(int)c]--;
        quantityMovements += 2;
    }

    for (int i = 0; i < n - 1; i++) {
        if (strcmp(output[i].abilities[0], output[i + 1].abilities[0]) == 0) {
            if (strcmp(output[i].name, output[i + 1].name) > 0) {
                Pokemon temp = output[i];

                output[i] = output[i + 1];
                output[i + 1] = temp;
                quantityMovements += 3;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        array[i] = output[i];
        quantityMovements++;
    }
}

/**
 * Realiza a ordenação dos Pokémon usando o algoritmo Radix Sort, com base em suas habilidades.
 *
 * @param array Ponteiro para o array de Pokémon.
 * @param n O número de Pokémon no array.
 */
void radixSort(Pokemon *array, int n) {
    int maximumLength = getMaximumLength(array, n); 

    for (int charIndex = maximumLength - 1; charIndex >= 0; charIndex--) {
        countSortByChar(array, n, charIndex);
    }
}

/**
 * Função principal do programa que lê um arquivo CSV contendo dados de Pokémon,
 * seleciona Pokémon com base em IDs fornecidos pelo usuário, os ordena utilizando
 * Radix Sort e exibe as informações dos Pokémon selecionados.
 */
int main() {
    long long start = now();
    FILE *file = fopen("/tmp/pokemon.csv", "r");

    if (file == NULL) {
        perror("Erro ao abrir arquivo.\n");
        return 1;
    }

    Pokemon pokedex[801];
    int comparisons = 0;
    int quantityPokemons = 0;

    readCsv(file, pokedex, &quantityPokemons);

    fclose(file);

    char number[256];
    Pokemon selectedPokemons[801];
    int id;
    int quantitySelectedPokemons = 0;
    bool found;

    scanf("%s", number);

    while(strcmp(number,"FIM") != 0) {
        id = atoi(number);
        found = false;

        int i = 0;

        while(found == false && i < 801) {
            comparisons++;

            if (atoi(pokedex[i].id) == id) {
                selectedPokemons[quantitySelectedPokemons] = pokedex[i];
                quantitySelectedPokemons++;
                found = true;
            }

            i++;
        }

        if (found == false) {
            printf("Pokemos com ID %d não encontrado.\n", id);
        }

        scanf("%s", number);
    }

    radixSort(selectedPokemons, quantitySelectedPokemons);

    for (int i = 0; i < quantitySelectedPokemons; i++) {
        displayInformation(&selectedPokemons[i]);
    }

    long long end = now();

    FILE *archive = fopen("847235_radixsort.txt", "w");

    if (archive == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(archive, "847235\t%d\t%d\t%lf", quantityComparisons, quantityMovements, (double)(end - start) / 1000.0);

    fclose(archive);

    return 0;
}