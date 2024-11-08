#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

/**
 * TP03Q07 - Fila com Alocação Flexível em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 08/11/2024
 */

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
Pokemon *search(Pokemon *pokemons, int id) {
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
Pokemon* readCsv(char fileName[]) {
    Pokemon *pokemons = (Pokemon *) malloc(801 * sizeof(Pokemon));

    if (!pokemons) {
        printf("Erro de alocação de memória.\n");
    }

    FILE* file = fopen(fileName, "r");

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

        if(isLegendary == 0) {
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
 * Estrutura que representa uma célula individual em uma fila encadeada.
 * Cada célula armazena um Pokémon e um ponteiro para a próxima célula,
 * permitindo a conexão entre os elementos da lista.
 */
struct Cell {
    Pokemon *pokemon;
    struct Cell *next;
} typedef Cell;

/**
 * Cria uma nova célula na fila encadeada para armazenar um Pokémon.
 * Aloca espaço na memória para uma nova célula, define o Pokémon
 * especificado e inicializa o ponteiro da próxima célula como NULL.
 *
 * @param pokemon Ponteiro para o Pokémon que será armazenado na célula.
 * @return Ponteiro para a nova célula criada.
 */
Cell *newCell(Pokemon *pokemon) {
    Cell *temp = (Cell *) malloc(sizeof(Cell));
    temp->pokemon = pokemon;
    temp->next = NULL;
    return temp;
}

/**
 * Estrutura de dados para uma fila de Pokémons.
 * 
 * Representa uma fila com operações de inserção e remoção, calculando a média da taxa de captura
 * dos Pokémons a cada inserção.
 */
struct Queue {
    struct Cell *first, *last;
    int size;
} typedef Queue;

/**
 * Inicializa uma nova fila vazia de Pokémons.
 *
 * @return Uma nova fila inicializada com o primeiro e último apontando para uma célula vazia.
 */
Queue newQueue() {
    Queue temp;
    temp.first = temp.last = newCell(NULL);
    temp.size = 0;
    return temp;
}

/**
 * Remove o primeiro elemento da fila e ajusta o tamanho.
 *
 * @param queue Ponteiro para a fila da qual o elemento será removido.
 * @return Ponteiro para o Pokémon removido, ou NULL se a fila estiver vazia.
 */
Pokemon *removal(Queue *queue) {
    if (queue->first == queue->last) {
        printf("\nA queue está vazia.\n");
    }

    Cell *temp = queue->first;
    queue->first = queue->first->next;
    queue->size--;

    free(temp);

    return queue->first->pokemon;
}

/**
 * Insere um novo Pokémon no final da fila. Caso a fila esteja cheia, remove o primeiro elemento.
 * Após a inserção, calcula e exibe a média arredondada da taxa de captura de todos os Pokémons na fila.
 *
 * @param queue Ponteiro para a fila onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido.
 */
void insert(Queue *queue, Pokemon *pokemon) {
    if (queue->size > 5 - 1) {
        removal(queue);
    }

    queue->last->next = newCell(pokemon);
    queue->last = queue->last->next;
    queue->size++;

    Cell *i = queue->first->next;
    int sum = 0;
    int k = 0;

    while (i != NULL) {
        sum += i->pokemon->captureRate;
        k++;
        i = i->next;
    }
        
    if (k > 0) {
        int roundedAverage = (int) round((double) sum / k);
        printf("Média: %d\n", roundedAverage);
    }
}

/**
 * Exibe as informações detalhadas dos Pokémons presentes na fila.
 * 
 * Para cada Pokémon na fila, exibe o índice, ID, nome, descrição, tipos, habilidades, 
 * peso, altura, taxa de captura, se é lendário ou não, geração e a data de captura.
 *
 * @param f Ponteiro para a fila cujos Pokémons serão exibidos.
 */
void displayInformation(Queue *f) {
    Cell *i;
    int count = 0;

    for (i = f->first->next; i != NULL; i = i->next) {
        printf("[%d] ", count++);
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
 * Verifica se a entrada corresponde ao comando de término.
 * 
 * Essa função checa se a string de entrada tem exatamente 3 caracteres e
 * se corresponde à sequência "FIM". Retorna verdadeiro se a condição for
 * satisfeita; caso contrário, retorna falso.
 * 
 * @param input String a ser verificada.
 * @return Verdadeiro se a entrada for "FIM", falso caso contrário.
 */
bool isEnd(char *input) {
    return (strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' && input[2] == 'M');
}

/**
 * Função principal que executa as operações de inserção e remoção em uma fila de Pokémons.
 * 
 * Lê os dados dos Pokémons a partir de um arquivo CSV, insere Pokémons na fila de acordo com
 * a entrada do usuário e executa operações adicionais com base nas instruções fornecidas pelo usuário.
 * Exibe os Pokémons removidos e, ao final, todas as informações detalhadas dos Pokémons restantes na fila.
 */
int main() {
    Pokemon* pokemons = readCsv("/tmp/pokemon.csv");

    Queue queuePokemons = newQueue();

    char input[30];
    int id;

    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);
        insert( &queuePokemons, search(pokemons, id));
    }

    int operationsNumber = 0;

    Pokemon *deletedPokemons;
    int k = 0;

    scanf("%d", &operationsNumber);

    for (int j = 0; j < operationsNumber; j++) {
        char *operation = (char *) malloc(sizeof(char) * 3);
        scanf("%s", operation);

        if (strcmp(operation, "I") == 0) { 
            int number;
            scanf("%d", &number);
            insert(&queuePokemons, search(pokemons, number));
        }
            
        if (strcmp(operation, "R") == 0) {
            deletedPokemons = removal(&queuePokemons);
            printf("(R) %s\n", deletedPokemons->name);
        }

        free(operation);
    }

    printf("\n");

    displayInformation(&queuePokemons);

    free(pokemons);

    return 0;
}