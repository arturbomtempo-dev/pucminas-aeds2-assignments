#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/**
 * TP02Q02 - Registro em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 29/09/2024
 */

/**
 * @struct Pokemon
 * @brief Estrutura que representa um Pokémon.
 *
 * Esta estrutura contém informações detalhadas sobre um Pokémon, incluindo 
 * seus atributos básicos.
 */
struct Pokemon {
    int id;
    int generation;
    char name[100];
    char description[100];
    char types[2][100];
    char abilities[10][100];
    double weightKg;
    double heightM;
    int captureRate;
    bool isLegendary;
    struct tm captureDate;
} typedef Pokemon;

/**
 * Exibe as informações detalhadas de um Pokémon.
 *
 * @param pokemon Estrutura do Pokémon a ser exibida.
 */
void displayInformation(Pokemon pokemon) {
    char dateBuffer[11];
    
    dateFormat(&pokemon.captureDate, dateBuffer);

    printf("[#%d -> %s: %s - [", pokemon.id, pokemon.name, pokemon.description);

    for (int i = 0; i < 2; i++) {
        if (strlen(pokemon.types[i]) > 0) {
            printf("'%s'%s", pokemon.types[i], (i < 2 - 1 && strlen(pokemon.types[i + 1]) > 0) ? ", " : "");
        }
    }

    printf("] - [");

    for (int i = 0; i < 10; i++) {
        if (strlen(pokemon.abilities[i]) > 0) {
            printf("'%s'%s", pokemon.abilities[i], (i < 10 - 1 && strlen(pokemon.abilities[i + 1]) > 0) ? ", " : "");
        }
    }

    printf("] - %.1fkg - %.1fm - %d%% - %s - %d gen] - %s\n", pokemon.weightKg, pokemon.heightM, pokemon.captureRate, pokemon.isLegendary ? "true" : "false", pokemon.generation, dateBuffer);
}

/**
 * A função abre o arquivo especificado, ignora a primeira linha (cabeçalho) e lê cada linha
 * subsequente para preencher a estrutura `Pokemon`. Ela verifica se o ID do Pokémon está na
 * lista de IDs buscados e, em caso afirmativo, armazena os dados do Pokémon na lista de Pokémon.
 * Se ocorrer algum erro na leitura de uma linha, uma mensagem de erro é exibida.
 *
 * @param filename Nome do arquivo CSV a ser lido.
 * @param searchedIDS Array contendo os IDs de Pokémon que devem ser buscados no arquivo.
 * @param count Número total de IDs a serem buscados.
 */
void readCSV(const char *filename, int searchedIDS[], int count) {
    FILE *file = fopen(filename, "r");
    
    if (file) {
        char line[100 * 20];

        fgets(line, sizeof(line), file);

        Pokemon pokemons[150] = {0};
        bool foundIDS[150] = {false};
        int foundPokemons = 0;

        while (fgets(line, sizeof(line), file) && foundPokemons < count) {
            Pokemon pokemon = { 0 };

            char abilities[100] = { 0 };
            char type1[100] = { 0 };
            char type2[100] = { 0 };
            char captureDate[100] = { 0 };
            int isLegendaryTemp = { 0 };

            if (sscanf(line, "%d,%d,%99[^,],%99[^,],%99[^,],%99[^,],\"%199[^\"]\",%lf,%lf,%d,%d,%99[^\n]", &pokemon.id, &pokemon.generation, pokemon.name, pokemon.description, type1, type2, abilities, &pokemon.weightKg, &pokemon.heightM, &pokemon.captureRate, &isLegendaryTemp, captureDate) != 12) {
                if (sscanf(line, "%d,%d,%99[^,],%99[^,],%99[^,],,\"%199[^\"]\",%lf,%lf,%d,%d,%99[^\n]", &pokemon.id, &pokemon.generation, pokemon.name, pokemon.description, type1, abilities, &pokemon.weightKg, &pokemon.heightM, &pokemon.captureRate, &isLegendaryTemp, captureDate) != 11) {
                    if (sscanf(line, "%d,%d,%99[^,],%99[^,],%99[^,],%99[^,],\"%199[^\"]\",,,%d,%d,%99[^\n]", &pokemon.id, &pokemon.generation, pokemon.name, pokemon.description, type1, type2, abilities, &pokemon.captureRate, &isLegendaryTemp, captureDate) != 10) {
                        if (sscanf(line, "%d,%d,%99[^,],%99[^,],%99[^,],,\"%199[^\"]\",,,%d,%d,%99[^\n]", &pokemon.id, &pokemon.generation, pokemon.name, pokemon.description, type1, abilities, &pokemon.captureRate, &isLegendaryTemp, captureDate) != 9) {
                            printf("Erro ao ler a line: %s\n", line);
                        }
                    }
                }
            }

            int passPokemon = 1;

            for (int i = 0; i < count; i++) {
                if (pokemon.id == searchedIDS[i]) {
                    passPokemon = 0;
                    break;
                }
            }

            if (passPokemon) {
                continue;
            }

            pokemon.isLegendary = isLegendaryTemp ? true : false;
            strncpy(pokemon.types[0], type1, 100);

            if (strlen(type2) > 0) {
                strncpy(pokemon.types[1], type2, 100);
            } else {
                pokemon.types[1][0] = '\0';
            }

            abilities[strcspn(abilities, "\n")] = '\0';

            char *start = strchr(abilities, '[');
            char *end = strchr(abilities, ']');

            if (start) {
                start++;
            }

            if (end) {
                *end = '\0';
            }

            char *token = strtok(start, ",");
            int abilityIndex = 0;

            while (token != NULL && abilityIndex < 10) {
                char cleanAbility[100];

                sscanf(token, " '%[^\']'", cleanAbility);
                strncpy(pokemon.abilities[abilityIndex++], cleanAbility, 100);
                token = strtok(NULL, ",");
            }

            int day, month, year;

            sscanf(captureDate, "%d/%d/%d", &day, &month, &year);

            pokemon.captureDate.tm_year = year - 1900;
            pokemon.captureDate.tm_mon = month - 1;
            pokemon.captureDate.tm_mday = day;

            for (int i = 0; i < count; i++) {
                if (searchedIDS[i] == pokemon.id && !foundIDS[i]) {
                    pokemons[i] = pokemon;
                    foundIDS[i] = true;
                    foundPokemons++;

                    break;
                }
            }
        }

        fclose(file);

        for (int i = 0; i < count; i++) {
            if (foundIDS[i]) {
                displayInformation(pokemons[i]);
            }
        }
    }
}

/**
 * Esta função recebe um Pokémon original e cria uma nova instância
 * do Pokémon com os mesmos atributos. Todos os campos do Pokémon original,
 * incluindo ID, geração, nome, descrição, tipos, habilidades, peso,
 * altura, taxa de captura, status de lendário e data de captura, são
 * copiados para o Pokémon clonado. 
 *
 * @param original O Pokémon a ser clonado.
 * @return Um novo objeto `Pokemon` que é uma cópia do Pokémon original.
 */
Pokemon clonePokemon(const Pokemon original) {
    Pokemon clone;

    clone.id = original.id;
    clone.generation = original.generation;

    strncpy(clone.name, original.name, 100);
    strncpy(clone.description, original.description, 100);

    for (int i = 0; i < 2; i++) {
        strncpy(clone.types[i], original.types[i], 100);
    }

    for (int i = 0; i < 10; i++) {
        strncpy(clone.abilities[i], original.abilities[i], 100);
    }

    clone.weightKg = original.weightKg;
    clone.heightM = original.heightM;
    clone.captureRate = original.captureRate;
    clone.isLegendary = original.isLegendary;
    clone.captureDate = original.captureDate;

    return clone;
}

/**
 * Esta função recebe uma estrutura `tm` que contém uma data e formata
 * essa data em uma string no formato "dd/mm/aaaa". A string formatada
 * é armazenada no buffer fornecido.
 *
 * @param date   Um ponteiro para a estrutura `tm` que contém a data a ser formatada.
 * @param buffer Um ponteiro para a string onde a data formatada será armazenada.
 */
void dateFormat(struct tm *date, char *buffer) {
    strftime(buffer, 11, "%d/%m/%Y", date);
}

/**
 * Esta função inicializa a execução do programa, permitindo que o usuário insira
 * IDs de Pokémon que deseja pesquisar. Os IDs são armazenados em um vetor e, 
 * quando o usuário digita "FIM", a função `readCSV` é chamada para ler os dados
 * dos Pokémon a partir de um arquivo CSV e exibir as informações dos Pokémon
 * correspondentes aos IDs fornecidos.
 */
int main() {
    int searchedIDS[150];
    int count = 0;

    char input[100] = { 0 };

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    while (strcmp(input, "FIM") != 0) {
        searchedIDS[count++] = atoi(input);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
    }

    readCSV("/tmp/pokemon.csv", searchedIDS, count);

    return 0;
}