#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

/**
 * TP04Q07 - Tabela Hash Indireta com Lista Simples
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 05/12/2024
 */

int comparisons = 0;
int movements = 0;

/**
 * Estrutura Date para representar uma data com dia, mês e ano.
 * 
 * Esta estrutura é útil para armazenar e manipular informações
 * de data de forma organizada, utilizando os campos `day`, `month` e `year`.
 */
struct Date {
    int day;
    int month;
    int year;
} typedef Date;

/**
 * Estrutura Pokemon para armazenar informações detalhadas sobre um Pokémon.
 * 
 * Esta estrutura contém dados essenciais, como ID, geração, nome, descrição, tipos,
 * habilidades, peso, altura, taxa de captura, status de lendário e data de captura.
 * Ela organiza as características de um Pokémon, permitindo fácil acesso e manipulação
 * das informações.
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
 * Função para buscar um Pokémon pelo ID em um array de Pokémons.
 * 
 * Esta função percorre o array de Pokémons fornecido e retorna um ponteiro
 * para o Pokémon cujo ID corresponde ao valor especificado. Caso o ID não
 * seja encontrado, o retorno pode ser um ponteiro não inicializado.
 * 
 * @param pokemons Array de Pokémons a ser pesquisado.
 * @param id Identificador do Pokémon a ser buscado.
 * @return Ponteiro para o Pokémon com o ID correspondente, ou um ponteiro não inicializado se não for encontrado.
 */
Pokemon* search(Pokemon *pokemons, int id) {
    Pokemon *pokemon;
    
    for (int i = 0; i < 801; i++) {
        if (pokemons[i].id == id) {
            pokemon = &pokemons[i];
        }
    }
    
    return pokemon; 
}

/**
 * Função para remover todas as ocorrências de um caractere específico em uma string.
 * 
 * Esta função percorre a string fornecida e remove todas as instâncias do caractere
 * especificado, movendo os caracteres restantes para preencher os espaços e garantindo
 * que a string resultante seja encerrada corretamente com um caractere nulo ('\0').
 * 
 * @param str Ponteiro para a string que será modificada.
 * @param character Caractere a ser removido da string.
 */
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

/**
 * Função para extrair um atributo de uma string com base em um delimitador.
 * 
 * Esta função localiza e retorna o próximo atributo na string, delimitado por
 * um caractere específico (ex.: vírgula). Caso o atributo esteja entre aspas,
 * ele é extraído sem as aspas. A função atualiza o ponteiro da string original
 * para a posição imediatamente após o delimitador ou o final do atributo.
 * 
 * @param str Ponteiro duplo para a string de onde o atributo será extraído.
 *            Após a execução, o ponteiro será atualizado para a posição seguinte
 *            ao atributo extraído.
 * @param delimiter Caractere delimitador que separa os atributos na string.
 * @return Ponteiro para o início do atributo extraído.
 */
char* removeAttribute(char **str, char delimiter) {
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
 * Função para ler dados de um arquivo CSV e carregar informações de Pokémons em um array.
 * 
 * Esta função abre um arquivo CSV contendo dados sobre Pokémons, lê cada linha e preenche
 * uma estrutura `Pokemon` com os dados correspondentes. Cada linha é processada e separada 
 * em atributos específicos como ID, geração, nome, tipos, habilidades, peso, altura, taxa de 
 * captura, status de lendário e data de captura. A função aloca dinamicamente memória para 
 * armazenar até 801 Pokémons e retorna um ponteiro para esse array.
 * 
 * Em caso de falha na alocação de memória ou na abertura do arquivo, a função exibe mensagens 
 * de erro e retorna um ponteiro `NULL`.
 * 
 * @param fileName Nome do arquivo CSV contendo os dados dos Pokémons.
 * @return Ponteiro para um array de `Pokemon` preenchido com os dados do arquivo, ou `NULL`
 *         em caso de erro.
 */
Pokemon *readCsv(char fileName[]) {
    Pokemon* pokemons = (Pokemon *) malloc(801 * sizeof(Pokemon));

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

/**
 * Salva os dados de execução em um arquivo especificado, contendo o número de comparações,
 * movimentos e o tempo total de execução em milissegundos.
 *
 * @param filename Nome do arquivo onde os dados de execução serão salvos.
 * @param totalTime Tempo total de execução em milissegundos.
 */
void saveExecutionFile(const char *Filename, long totalTime) {
    FILE *file = fopen(Filename, "w+");

    if (file == NULL) {
        printf("Erro ao gerar o arquivo.\n");
    } else {
        fprintf(file, "847235\t%d\t%d\t%ldms", comparisons, movements, totalTime);
        fclose(file);
    }
}

/**
 * Estrutura que representa uma célula de uma lista encadeada.
 * Cada célula contém um ponteiro para um objeto `Pokemon` e um ponteiro para a próxima célula.
 */
struct Cell {
    Pokemon *pokemon;
    struct Cell *next;
} typedef Cell;

/**
 * Função que cria uma nova célula para armazenar um Pokémon.
 * A célula criada aponta para o Pokémon fornecido e o próximo ponteiro é inicializado como NULL.
 * 
 * @param pokemon Ponteiro para o objeto `Pokemon` a ser armazenado na célula.
 * @return Ponteiro para a nova célula criada.
 */
Cell* newCell(Pokemon *pokemon) {
    Cell *temp = (Cell *) malloc(sizeof(Cell));
    temp->pokemon = pokemon;
    temp->next = NULL;
    return temp;
}

/**
 * Estrutura que representa uma lista encadeada de Pokémon.
 * Contém ponteiros para a primeira e última célula da lista, além do tamanho total da lista.
 */
struct List {
    struct Cell *first, *last;
    int size;
} typedef List;

/**
 * Função que cria uma nova lista encadeada vazia.
 * A lista criada possui uma célula inicial (`first` e `last`) que aponta para uma célula "nula" 
 * (indicando que a lista está vazia) e seu tamanho é inicializado como 0.
 * 
 * @return Ponteiro para a nova lista criada.
 */
List* newList() {
    List *temp = (List *) malloc(sizeof(List));;
    temp->first = temp->last = newCell(NULL);
    temp->size = 0;
    return temp;
}

/**
 * A função cria uma nova célula para o Pokémon fornecido, ajusta os ponteiros de forma que a nova célula
 * seja inserida no início da lista, e atualiza o tamanho da lista.
 * 
 * @param list Ponteiro para a lista onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido na lista.
 */
void insertStart(List *list, Pokemon *pokemon) {
    Cell *temp = newCell(pokemon);

    temp->next = list->first;
    list->first->pokemon = pokemon;
    list->first = temp;
    list->size++;
}

/**
 * A função cria uma nova célula para o Pokémon fornecido, ajusta os ponteiros de forma que a nova célula
 * seja inserida no final da lista, e atualiza o tamanho da lista.
 * 
 * @param list Ponteiro para a lista onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido na lista.
 */
void insertEnd(List *list, Pokemon *pokemon) {
    list->last->next = newCell(pokemon);
    list->last = list->last->next;
    list->size++;
}

/**
 * A função percorre a lista a partir do segundo elemento e compara o nome de cada Pokémon com o nome fornecido.
 * Se encontrar um Pokémon com o nome correspondente, retorna `true`. Caso contrário, retorna `false`.
 * 
 * @param list Ponteiro para a lista onde o Pokémon será buscado.
 * @param name Nome do Pokémon a ser buscado na lista.
 * @return `true` se o Pokémon for encontrado na lista, `false` caso contrário.
 */
bool searchList(List *list, char *name) {
    Cell *i;
    bool response = false;

    for (i = list->first->next; i != NULL; i = i->next) {
        comparisons++;

        if (strcmp(i->pokemon->name, name) == 0) {
            response = true;
        }
    }

    return response;
}

List **table;
int size;

/**
 * Cria e inicializa uma tabela hash indireta com listas encadeadas.
 * A tabela hash é alocada dinamicamente com base no tamanho `n` especificado e cada posição da tabela 
 * é uma lista encadeada (representada por um ponteiro para `List`). Cada lista é inicializada com um 
 * nó inicial vazio.
 * 
 * @param n O número de posições que a tabela hash deve ter.
 */
void indirectHashList(int n) {
    size = n;
    table = (List**) malloc (size * sizeof(List*));

    for (int i = 0; i < size; i++) {
        table[i] = newList();
    }
}


/**
 * Esta função chama `indirectHashList` passando o valor 21 como parâmetro, 
 * criando uma tabela hash com 21 listas encadeadas.
 */
void newIndirectHashList() {
    indirectHashList(21);
}

/**
 * A função calcula a soma dos valores ASCII dos caracteres do nome fornecido e
 * retorna o valor da soma módulo o tamanho da tabela hash. Isso fornece um índice
 * dentro da tabela para armazenar ou buscar o Pokémon correspondente.
 * 
 * @param name O nome do Pokémon para gerar o índice.
 * @return O índice calculado para o nome fornecido.
 */
int h(char* name) {
    int sum = 0;
    for (int i = 0; i < strlen(name); sum += (int) name[i], i++);
    return sum % size;
}

/**
 * A função calcula o índice usando a função hash (`h`) e busca na lista encadeada 
 * correspondente a esse índice. Se o Pokémon for encontrado, retorna a posição na tabela, 
 * caso contrário, retorna -1.
 * 
 * @param name O nome do Pokémon a ser buscado na tabela hash.
 * @return A posição na tabela hash onde o Pokémon foi encontrado, ou -1 se não encontrado.
 */
int hashSearch(char *name) {
    int position = h(name);
    bool response = searchList(table[position], name);
    return response ? position : -1;
}

/**
 * A função calcula o índice usando a função hash (`h`) e insere o Pokémon no início da lista
 * encadeada correspondente a esse índice. O Pokémon é adicionado usando a função `insertStart`.
 * 
 * @param pokemon O Pokémon a ser inserido na tabela hash.
 */
void hashInsert(Pokemon *pokemon) {
    int position = h(pokemon->name);
    insertStart(table[position], pokemon);
}

/**
 * Verifica se a entrada indica o término da execução.
 *
 * @param input String de entrada a ser avaliada.
 * @return `true` se a entrada for "FIM", `false` caso contrário.
 */
bool isEnd(char* input) {
    return (strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' && input[2] == 'M');
}

/**
 * Função principal que lê os dados dos Pokémon de um arquivo CSV, insere-os em uma tabela hash 
 * indireta e realiza buscas pelos nomes dos Pokémon. O tempo de execução é medido e salvo em um 
 * arquivo de log. A memória alocada é liberada antes do término do programa.
 */
int main() {
    clock_t startClock, endClock;
    double totalTime;

    Pokemon *pokemons = readCsv("/tmp/pokemon.csv");

    newIndirectHashList();

    int id;
    char input[30];

    startClock = clock();
    
    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);
        hashInsert(search(pokemons, id));
    }

    while (scanf("%s", input) && !isEnd(input)) {
        int response = hashSearch(input);
        response != -1 ? printf("=> %s: (Posicao: %d) SIM\n", input, response ) : printf("=> %s: NAO\n", input);
    }

    endClock = clock();
    totalTime = ((double)(endClock - startClock));

    saveExecutionFile("847235_hashIndireta.txt", totalTime);

    free(pokemons);

    return 0;
}