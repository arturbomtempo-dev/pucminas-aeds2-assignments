#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/**
 * TP03Q08 - Quicksort com LISTA DINÂMICA DUPLAMENTE ENCADEADA em C
 * 
 * @author Artur Bomtempo Colen
 * @version 2.0, 11/11/2024
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
    int dia;
    int mes;
    int ano;
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
Pokemon *search(Pokemon* pokemons, int id) {
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

        sscanf(removeAttribute(&token, '/'), "%d", &temp->captureDate.dia);
        sscanf(removeAttribute(&token, '/'), "%d", &temp->captureDate.mes);
        sscanf(removeAttribute(&token, '/'), "%d", &temp->captureDate.ano);

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
void saveExecutionFile(const char *filename, long totalTime) {
    FILE *file = fopen(filename, "w+");

    if (file == NULL) {
        printf("Erro ao gerar o arquivo.\n");
    } else {
        fprintf(file, "847235\t%d\t%d\t%ldms", comparisons, movements, totalTime);
        
        fclose(file);
    }
}

/**
 * Estrutura que representa uma célula dupla na lista duplamente encadeada.
 * Cada célula armazena um ponteiro para um Pokémon e possui ponteiros para
 * a célula anterior e a próxima célula da lista.
 */
struct DoubleCell {
    Pokemon *pokemon;
    struct DoubleCell *next, *previous;
} typedef DoubleCell;

/**
 * Cria uma nova célula dupla para a lista duplamente encadeada.
 * 
 * @param pokemon Ponteiro para o Pokémon a ser armazenado na nova célula.
 * @return Ponteiro para a nova célula inicializada.
 */
DoubleCell *newDoubleCell(Pokemon *pokemon) {
    DoubleCell *temp = (DoubleCell *) malloc(sizeof(DoubleCell));
    temp->pokemon = pokemon;
    temp->previous = NULL;
    temp->next = NULL;
    return temp;
}

/**
 * Estrutura que representa uma lista duplamente encadeada, com ponteiros para 
 * a primeira e última célula e um campo para armazenar o tamanho da lista.
 */
struct DoubleList {
    struct DoubleCell *first, *last;
    int size;
} typedef DoubleList;

/**
 * Cria uma nova lista duplamente encadeada vazia.
 * 
 * @return Ponteiro para a nova lista inicializada.
 */
DoubleList *newDoubleList() {
    DoubleList *temp = (DoubleList *) malloc(sizeof(DoubleList));
    temp->first = temp->last = newDoubleCell(NULL);
    temp->size = 0;
    return temp;
}

/**
 * Insere um Pokémon no início da lista duplamente encadeada.
 * 
 * @param list Ponteiro para a lista onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido na lista.
 */
void insertStart(DoubleList *list, Pokemon *pokemon) {
    DoubleCell *temp = newDoubleCell(pokemon);
    temp->next = list->first;

    list->first->pokemon = pokemon;
    list->first->previous = temp; 
    list->first = temp;
    list->size++;
}

/**
 * Insere um Pokémon no final da lista duplamente encadeada.
 * 
 * @param list Ponteiro para a lista onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido no final da lista.
 */
void insertEnd(DoubleList *list, Pokemon *pokemon) {
    list->last->next = newDoubleCell(pokemon);
    list->last->next->previous = list->last;
    list->last = list->last->next;
    list->size++;
}

/**
 * Remove e retorna o Pokémon da última posição da lista.
 * 
 * @param list Ponteiro para a lista da qual o Pokémon será removido.
 * @return Ponteiro para o Pokémon removido ou NULL se a lista estiver vazia.
 */
Pokemon *removeEnd(DoubleList *list) {
    if (list->first == list->last) {
        printf("\nA lista está vazia.\n");
        return 0;
    }

    DoubleCell *temp = list->last;
    Pokemon *pokemon = temp->pokemon;

    list->last = list->last->previous;
    list->last->next = NULL;
    list->size--;

    free(temp);

    return pokemon;
}

/**
 * Remove e retorna o Pokémon de uma posição específica da lista.
 * 
 * @param list Ponteiro para a lista da qual o Pokémon será removido.
 * @param position Posição do Pokémon na lista a ser removido.
 * @return Ponteiro para o Pokémon removido ou NULL se a posição for inválida.
 */
Pokemon *removal(DoubleList *list, int position) {
    if (list->first == list->last) {
        printf("\nA lista está vazia.\n");
        return NULL;
    } else if (position < 0 || position > list->size - 1) {
        printf("Erro ao tentar remover item da posição (%d/ tamanho = %d) inválida.", position, list->size);
        return NULL;
    } else if (position == list->size - 1) {
        return removeEnd(list);
    } else {
        DoubleCell *previous = list->first;

        for (int i = 0; i < position; i++) {
            previous = previous->next;
        }

        DoubleCell *temp = previous->next;
        Pokemon *pokemon = temp->pokemon;

        previous->next = temp->next;

        free(temp);

        if (position == list->size - 1) {
            list->last = previous;
        }
        
        list->size--;

        return pokemon;
    }
}

/**
 * Exibe todas as informações dos Pokémons presentes na lista duplamente encadeada.
 * Para cada Pokémon na lista, são exibidos: ID, nome, descrição, tipos, habilidades,
 * peso, altura, taxa de captura, status de lendário, geração e data de captura.
 * 
 * @param l Ponteiro para a lista duplamente encadeada que será exibida.
 */
void displayList(DoubleList *l) {
    DoubleCell *i;
    int count = 0;

    for (i = l->first->next; i != NULL; i = i->next) {
        printf("[#%d -> %s: %s - ", i->pokemon->id, i->pokemon->name, i->pokemon->description);
        printf("['%s'", i->pokemon->type[0]);

        if (strlen(i->pokemon->type[1]) > 0) {
            printf(", '%s'", i->pokemon->type[1]);
        }

        printf("] - [");

        for (int j = 0; strlen(i->pokemon->abilities[j]) > 0; j++) {
            printf("'%s'", i->pokemon->abilities[j]);

            if (strlen(i->pokemon->abilities[j + 1]) > 0) {
                printf(", ");
            }
        }

        printf("] - ");

        printf("%.1lfkg - %.1lfm - %d%% - %s - %d gen] - %02d/%02d/%d\n", 
            i->pokemon->weight, 
            i->pokemon->height, 
            i->pokemon->captureRate, 
            i->pokemon->isLegendary ? "true" : "false", 
            i->pokemon->generation,
            i->pokemon->captureDate.dia, 
            i->pokemon->captureDate.mes, 
            i->pokemon->captureDate.ano
        );
    }
}

/**
 * Libera a memória de todos os elementos da lista duplamente encadeada,
 * removendo cada célula até que a lista esteja vazia. 
 * Também libera a célula inicial fictícia da lista.
 * 
 * @param list Ponteiro para a lista duplamente encadeada que será deletada.
 */
void deleteList(DoubleList *list) {
    while (list->size > 0) {
        removal(list,0);
    }

    free(list->first);
}

/**
 * Obtém o elemento da lista duplamente encadeada na posição especificada.
 * 
 * A função percorre a lista até a posição fornecida e retorna o ponteiro
 * para a célula (DoubleCell) que está naquela posição. Se a posição for
 * inválida (fora dos limites da lista), a função retorna NULL.
 * 
 * @param list Ponteiro para a lista duplamente encadeada.
 * @param position A posição do elemento desejado na lista.
 * @return Ponteiro para a célula na posição especificada, ou NULL se a posição for inválida.
 */
DoubleCell* getPivot(DoubleList *list, int position) {
    DoubleCell *current = list->first->next;

    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }

    return current;
}

/**
 * Troca os elementos (Pokemons) entre duas células da lista duplamente encadeada.
 * 
 * A função recebe duas células da lista e troca os valores dos Pokémon armazenados nelas.
 * O ponteiro do Pokémon na célula `ci` é trocado com o ponteiro do Pokémon na célula `cj`.
 * 
 * @param list Ponteiro para a lista duplamente encadeada (não utilizado diretamente na troca, mas necessário por consistência).
 * @param ci Ponteiro para a célula que contém o primeiro Pokémon a ser trocado.
 * @param cj Ponteiro para a célula que contém o segundo Pokémon a ser trocado.
 */
void swap(DoubleList *list, DoubleCell *ci, DoubleCell *cj) {
    Pokemon *temp = ci->pokemon;
    ci->pokemon = cj->pokemon;
    cj->pokemon = temp;
}

/**
 * Ordena uma lista duplamente encadeada utilizando o algoritmo de QuickSort.
 * 
 * @param list Ponteiro para a lista duplamente encadeada a ser ordenada.
 * @param left Índice da posição inicial da sublista a ser ordenada.
 * @param right Índice da posição final da sublista a ser ordenada.
 * @param cLeft Ponteiro para a célula à esquerda da sublista.
 * @param cRight Ponteiro para a célula à direita da sublista.
 */
void quickSort(DoubleList *list, int left, int right, DoubleCell *cLeft, DoubleCell *cRight) {
    DoubleCell *ci = cLeft, *cj = cRight;
    int i = left, j = right;
    DoubleCell *pivot = getPivot(list, left);

    while (i <= j) {
        while ((ci->pokemon->generation < pivot->pokemon->generation || (ci->pokemon->generation == pivot->pokemon->generation && strcmp(ci->pokemon->name, pivot->pokemon->name) < 0))) {
            comparisons++;
            i++;

            if (ci->next != NULL) {
                ci = ci->next;
            }
        }

        while ((cj->pokemon->generation > pivot->pokemon->generation || (cj->pokemon->generation == pivot->pokemon->generation && strcmp(cj->pokemon->name, pivot->pokemon->name) > 0))) {
            comparisons++;
            j--;

            if (cj->previous != NULL) {
                cj = cj->previous;
            }
        }

        if (i <= j) {
            movements += 3;

            swap(list, ci, cj);

            if (ci->next != NULL) {
                ci = ci->next;
            }

            i++;

            if (cj->previous != NULL) {
                cj = cj->previous;
            }

            j--;
        }
    }

    if (left < j) {
        quickSort(list, left, j, cLeft, cj);
    }

    if (i < right) {
        quickSort(list, i, right, ci, cRight);
    }
}

/**
 * Verifica se a entrada corresponde ao comando de término.
 * 
 * Essa função checa se a string de entrada tem exatamente 3 caracteres e
 * se corresponde à sequência "FIM". Retorna verdadeiro se a condição for
 * satisfeita; caso contrário, retorna falso.
 * 
 * @param input String a ser verificada.
 * @return Verdadeiro se a entrada for "FIM", falso caso contrário.
 */
bool isEnd(char* input) {
    return (strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' && input[2] == 'M');
}

/**
 * Função principal que executa o programa de ordenação de Pokémon com base em um arquivo CSV.
 * 
 * O programa lê um arquivo CSV contendo dados de Pokémon e os insere em uma lista duplamente encadeada. 
 * Em seguida, ele ordena a lista utilizando o algoritmo QuickSort, com base na geração do Pokémon e, em caso de empate, pelo nome.
 * O tempo total de execução do algoritmo é medido e salvo em um arquivo de execução. Após a ordenação, a lista de Pokémon é exibida.
 */
int main() {
    clock_t startClock, endClock;
    double totalTime;

    Pokemon* pokemons = readCsv("/tmp/pokemon.csv");

    DoubleList *pokemonsList = newDoubleList();

    char input[30];
    int id;
    
    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);
        insertEnd( pokemonsList, search(pokemons, id));
    }

    startClock = clock();

    quickSort(pokemonsList, 0, pokemonsList->size - 1, pokemonsList->first->next, pokemonsList->last);

    endClock = clock();

    displayList(pokemonsList);

    totalTime = ((double)(endClock - startClock));

    saveExecutionFile("847235_quicksort2.txt", totalTime);

    free(pokemons);

    deleteList(pokemonsList);

    return 0;
}