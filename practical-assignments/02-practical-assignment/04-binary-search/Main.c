#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/**
 * TP02Q04 - Pesquisa Binária
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 10/10/2024
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
 * A função percorre o array de Pokémon, ordenado pelo nome, 
 * usando o algoritmo de busca binária. A cada comparação realizada, 
 * o contador de comparações é incrementado.
 * 
 * @param pokemons Array de ponteiros para Pokémon.
 * @param name Nome do Pokémon a ser buscado.
 * @param comparisons Ponteiro para o contador de comparações.
 * @return Retorna um ponteiro para o Pokémon encontrado, ou NULL se não encontrado.
 */
Pokemon *binarySearchPokemon(Pokemon **pokemons, char *name, int *comparisons) {
    int right = 801 - 1, left = 0, middle;

    while (left <= right) {
        middle = (left + right) / 2;

        int comparison = strcmp(name, pokemons[middle]->name);
        (*comparisons)++;

        if (comparison == 0) {
            return pokemons[middle];
        } else if (comparison > 0) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return NULL;
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

/**
 * A função abre um arquivo de texto para escrita e salva os resultados da execução,
 * incluindo o tempo de CPU utilizado e o número de comparações realizadas. 
 * Se ocorrer um erro ao abrir o arquivo, uma mensagem de erro será exibida.
 * 
 * @param fileName Nome do arquivo onde os resultados serão salvos.
 * @param cpuTimeEndUsed Tempo de CPU utilizado (em milissegundos).
 * @param comparisons Número de comparações realizadas durante a execução.
 */
void saveExecutionFile(const char *fileName, long cpuTimeEndUsed, int comparisons) {
    FILE *file = fopen(fileName, "w+");

    if (file == NULL) {
        printf("Erro ao gerar o arquivo.\n");
    } else {
        fprintf(file, "847235\t%ldms\t%d", cpuTimeEndUsed, comparisons);
        fclose(file);
    }
}

/**
 * A função realiza a troca de posição de dois elementos em um array de ponteiros 
 * para Pokémon, usando as posições indicadas pelos índices fornecidos.
 * 
 * @param pokemon Array de ponteiros para Pokémon.
 * @param i Índice do primeiro Pokémon a ser trocado.
 * @param j Índice do segundo Pokémon a ser trocado.
 */
void swap(Pokemon **pokemon, int i, int j) {
    Pokemon *tmp = pokemon[i];
    pokemon[i] = pokemon[j];
    pokemon[j] = tmp;
}

/**
 * A função realiza a ordenação dos Pokémons com base nos seus nomes. Utiliza 
 * o algoritmo Quicksort para realizar a ordenação de forma recursiva, escolhendo 
 * um pivô e dividindo o array até que esteja ordenado.
 * 
 * @param pokemon Array de ponteiros para Pokémon.
 * @param left Índice inicial do array a ser ordenado.
 * @param right Índice final do array a ser ordenado.
 */
void quicksort(Pokemon **pokemon, int left, int right) {
    int i = left, j = right;
    char* pivot = pokemon[(left + right) / 2]->name;

    while (i <= j) {
        while (strcmp(pokemon[i]->name, pivot) < 0) {
            i++;
        }

        while (strcmp(pokemon[j]->name, pivot) > 0) { 
            j--;
        }

        if (i <= j) {
            swap(pokemon, i, j);  
            i++;
            j--;
        }
    }

    if (left < j) {
        quicksort(pokemon, left, j);
    }

    if (i < right) {
        quicksort(pokemon, i, right);
    }
}

/**
 * Esta função realiza a leitura de dados dos Pokémon de um arquivo CSV, 
 * ordena os Pokémon utilizando o algoritmo QuickSort e 
 * permite a busca dos Pokémon por ID e nome, 
 * registrando o tempo de execução e o número de comparações feitas.
 */
int main() {
    clock_t start, end;
    double cpuTimeEndUsed;
    int comparisons = 0;

    start = clock();

    Pokemon* pokemons = readCsv("/tmp/pokemon.csv");
    
    if (!pokemons) {
        printf("Pokemons nao inicializados\n");
        return 1;
    }

    Pokemon *pokemonPointers[801];

    for (int i = 0; i < 801; i++) {
        pokemonPointers[i] = &pokemons[i];
    }

    quicksort(pokemonPointers, 0, 801 - 1);

    char input[20];
    int ids[100];
    int i = 0;
    
    while (scanf("%s", input) && strcmp(input, "FIM") != 0) {
        sscanf(input, "%d", &ids[i++]);
    }

    char names[100][100]; 

    int p = 0;
    
    while (scanf("%s", input) && strcmp(input, "FIM") != 0) {
        strcpy(names[p++], input);
    }

    for (int j = 0; j < p; j++) {
        bool found = false;
        Pokemon *foundPokemon = binarySearchPokemon(pokemonPointers, names[j], &comparisons);

        if (foundPokemon != NULL) {
            for (int k = 0; k < i; k++) {
                if (foundPokemon->id == ids[k]) { 
                    found = true;
                    comparisons++;
                }
            }
        }

        if(found) {
            printf("SIM\n");
        }
        else {
            printf("NAO\n");
        }
    }

    end = clock();
    cpuTimeEndUsed = ((double)(end - start));

    saveExecutionFile("847235_binaria.txt", cpuTimeEndUsed, comparisons);

    free(pokemons);

    return 0;
}