#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * TP02Q02 - Registro em C
 * 
 * @author Artur Bomtempo Colen
 * @version 2.0, 10/10/2024
 */

/**
 * @struct Date
 * @brief Estrutura usada para representar a data de captura de um Pokémon.
 * 
 * A estrutura Date armazena informações de uma data, composta por dia, mês e ano,
 * facilitando a formatação e manipulação de datas relacionadas à captura de Pokémon.
 */
struct Date {
    int day;
    int month;
    int year;
} typedef Date;

/**
 * @struct Pokemon
 * @brief Estrutura usada para representar um Pokémon e suas principais características.
 * 
 * A estrutura Pokemon contém informações detalhadas sobre um Pokémon, incluindo seu 
 * identificador único, atributos físicos, habilidades, taxa de captura, geração e a data de captura.
 */
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

/**
 * Esta função percorre uma lista de Pokémons e busca aquele que possui o ID fornecido. 
 * Retorna um ponteiro para o Pokémon encontrado.
 * 
 * @param pokemons Um ponteiro para a lista de Pokémons.
 * @param id O ID do Pokémon a ser buscado.
 * @return Um ponteiro para o Pokémon encontrado. Se o ID não for encontrado, retorna NULL.
 */
Pokemon *searchPokemon(Pokemon *pokemons, int id) {
    Pokemon *pokemon;
    
    for (int i = 0; i < 801; i++) {
        if (pokemons[i].id == id) {
            pokemon = &pokemons[i];
        }
    }
    
    return pokemon; 
}

/**
 * Esta função percorre a string original e remove todas as ocorrências do caractere
 * fornecido, deslocando os demais caracteres para preencher os espaços removidos.
 * 
 * @param str A string original a ser modificada.
 * @param value O caractere a ser removido da string.
 */
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

/**
 * A função busca pelo próximo delimitador (ou aspas, se for o caso) na string fornecida.
 * O trecho encontrado é removido da string original e retornado. A string original
 * é atualizada para continuar após o delimitador encontrado.
 * 
 * @param str Um ponteiro para a string original que será modificada. Após a execução, o ponteiro será atualizado para apontar para o próximo segmento da string.
 * @param delimiter O caractere delimitador que indica o fim do atributo a ser removido.
 * @return O atributo removido da string original. 
 */
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

/**
 * A função aloca dinamicamente um array de estruturas `Pokemon` para armazenar até 801 Pokémons.
 * Em seguida, ela lê as linhas do arquivo CSV, extrai os dados de cada Pokémon e preenche
 * o array com essas informações. Se houver erro de alocação de memória ou na abertura do
 * arquivo, mensagens de erro serão exibidas.
 *
 * @param fileName O nome do arquivo CSV a ser lido.
 * @return Um ponteiro para o array de Pokémons preenchido com os dados do arquivo. 
 *         Se ocorrer erro, o retorno será `NULL`.
 */
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

/**
 * A função imprime os dados do Pokémon, como ID, nome, descrição, tipos,
 * habilidades, peso, altura, taxa de captura, se é lendário ou não, geração,
 * e data de captura em um formato padronizado.
 *
 * @param pokemon A estrutura Pokemon cujas informações serão exibidas.
 */
void displayInformation(Pokemon pokemon) {
    printf("[#%d -> %s: %s - ", pokemon.id, pokemon.name, pokemon.description);

    printf("['%s'", pokemon.type[0]);

    if (strlen(pokemon.type[1]) > 0) {
        printf(", '%s'", pokemon.type[1]);
    }

    printf("] - [");

    for (int i = 0; strlen(pokemon.abilities[i]) > 0; i++) {
        printf("'%s'", pokemon.abilities[i]);

        if (strlen(pokemon.abilities[i + 1]) > 0) {
            printf(", ");
        }
    }

    printf("] - ");

    printf("%.1lfkg - %.1lfm - %d%% - %s - %d gen] - %02d/%02d/%d\n", 
           pokemon.weight, 
           pokemon.height, 
           pokemon.captureRate, 
           pokemon.isLegendary ? "true" : "false", 
           pokemon.generation,
           pokemon.captureDate.day, 
           pokemon.captureDate.month, 
           pokemon.captureDate.year);
}

/**
 * Função principal do programa, que gerencia a leitura de dados de Pokémon
 * e permite a busca e exibição de informações sobre os Pokémon com base
 * em IDs fornecidos pelo usuário.
 */
int main() {
    int id;
    char input[20];
    
    Pokemon *pokemons = readCsv("tmp/pokemon.csv");

    if (!pokemons) {
        printf("Pokemons não inicializados.\n");
    }
    
    while (scanf("%s", input) && strcmp(input, "FIM")) {
        sscanf(input, "%d", &id);

        Pokemon *foundPokemon = searchPokemon(pokemons, id);
        
        if (id <= 801) {
            displayInformation(*foundPokemon);
        }
    }

    free(pokemons);

    return 0;
}