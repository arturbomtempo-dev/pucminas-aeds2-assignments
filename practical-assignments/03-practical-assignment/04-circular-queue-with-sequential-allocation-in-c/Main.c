#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

/**
 * TP03Q04 - Fila Circular com Alocação Sequencial em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 04/11/2024
 */

#define true 1
#define false 0

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
void removeOccurrences(char *str, char characters) {
    int i, j = 0;
    size_t length = strlen(str);
    
    for (i = 0; i < length; i++) {
        if (str[i] != characters) {
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
    Pokemon *pokemons = (Pokemon*) malloc (801 * sizeof(Pokemon));

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

        char *tokenAbilities = abilitiesString;
        int indexAbilities = 0;

        while (*tokenAbilities != '\0' && indexAbilities < 10) {
            while (isspace(*tokenAbilities)) {
                tokenAbilities++;
            }

            char *startAbilities = tokenAbilities;
            char *endAbilities;
            
            if (*startAbilities == '\'') {
                startAbilities++;
                endAbilities = strchr(startAbilities, '\'');
            } else {
                endAbilities = strchr(startAbilities, ','); 
            }

            if (endAbilities != NULL) {
                *endAbilities = '\0'; 
                strcpy(temp->abilities[indexAbilities], startAbilities);
                indexAbilities++;
                tokenAbilities = endAbilities + 1;
            } else {
                strcpy(temp->abilities[indexAbilities], startAbilities);
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

Pokemon *array[6 + 1];
int first, last;

/**
 * Inicializa a fila circular definindo o contador de elementos como 0.
 * 
 * Essa função prepara a fila circular para receber novos elementos.
 */
void start() {
   first = 0;
   last = 0;
}

/**
 * Remove e retorna o primeiro elemento da fila circular de Pokémons.
 *
 * Esta função verifica se a fila está vazia antes de tentar remover o 
 * elemento. Caso esteja vazia, exibe uma mensagem de erro e encerra o 
 * programa. Caso contrário, remove o elemento na posição indicada por 
 * `first`, atualiza o índice `first` para o próximo elemento na fila e 
 * retorna o Pokémon removido.
 *
 * @return Pokemon* - Ponteiro para o Pokémon removido.
 */
Pokemon *removal() {
    if (first == last) {
        printf("Erro ao remover.");
        exit(1);
    }
    
    Pokemon *temp = array[first];
    first = (first + 1) % 6;
    return temp;
}

/**
 * Insere um Pokémon na fila circular e calcula a média arredondada da taxa de captura.
 *
 * Esta função insere um Pokémon no índice `last` da fila circular. Se a fila estiver 
 * cheia, o elemento mais antigo é removido antes da inserção. Após a inserção, a 
 * função percorre todos os elementos na fila para calcular a média da taxa de captura 
 * (`captureRate`) dos Pokémons, arredondando o valor e exibindo-o na tela.
 *
 * @param x Pokemon* - Ponteiro para o Pokémon a ser inserido na fila.
 */
void insert(Pokemon *x) {
    if (((last + 1) % 6) == first) {
        removal();
    }

    array[last] = x;
    last = (last + 1) % 6;
    
    int i = first;
    int sum = 0;
    int k = 0;

    while (i != last) {
        sum += array[i]->captureRate;
        i = ((i + 1) % 6);
        k++;
    }
        
    if (k > 0) {
        int roundedAverage = (int) round((double) sum / k);
        printf("Média: %d\n", roundedAverage);
    }
}

/**
 * Exibe as informações de todos os Pokémons na fila circular.
 * 
 * As informações são formatadas e exibidas no console.
 */
void displayInformation() {
   int i = first;
   int k = 0;

   printf("\n");

   while (i != last) {
        printf("[%d] ", k++);
        printf("[#%d -> %s: %s - ", array[i]->id, array[i]->name, array[i]->description);

        printf("['%s'", array[i]->type[0]);

        if (strlen(array[i]->type[1]) > 0) {
            printf(", '%s'", array[i]->type[1]);
        }

        printf("] - [");

        for (int j = 0; strlen(array[i]->abilities[j]) > 0; j++) {
            printf("'%s'", array[i]->abilities[j]);

            if (strlen(array[i]->abilities[j + 1]) > 0) {
                printf(", ");
            }
        }

        printf("] - ");

        printf("%.1lfkg - %.1lfm - %d%% - %s - %d gen] - %02d/%02d/%d\n", 
            array[i]->weight, 
            array[i]->height, 
            array[i]->captureRate, 
            array[i]->isLegendary ? "true" : "false", 
            array[i]->generation,
            array[i]->captureDate.day, 
            array[i]->captureDate.month, 
            array[i]->captureDate.year);

        i = ((i + 1) % 6);
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
 * Função principal que gerencia o fluxo de operações na fila circular de Pokémons.
 *
 * A função `main` realiza as seguintes operações:
 * 1. Inicializa a fila circular.
 * 2. Lê os dados dos Pokémons a partir de um arquivo CSV e os armazena em um array.
 * 3. Lê entradas do usuário para inserir Pokémons na fila até receber o comando de finalização.
 * 4. Lê o número de operações adicionais e executa operações de inserção e remoção na fila com base nos comandos:
 *    - "I": Insere um Pokémon na fila circular.
 *    - "R": Remove o Pokémon mais antigo da fila e exibe seu nome.
 * 5. Exibe as informações dos Pokémons atualmente na fila.
 * 6. Libera a memória alocada para a lista de Pokémons lida do CSV.
 */
int main() {
    start();

    Pokemon *pokemons = readCsv("/tmp/pokemon.csv");

    char input[30];
    int id;
    
    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);

        insert(search(pokemons, id));
    }

    int numberOperations = 0;
    Pokemon *excludedPokemon;
    int k = 0;

    scanf("%d", &numberOperations);

    for (int j = 0; j < numberOperations; j++) {
        char *operation = (char *) malloc(sizeof (char) * 3);
        scanf("%s", operation);

        if (strcmp(operation, "I") == 0) {
            int number;
            scanf("%d", &number);
            insert(search(pokemons, number));
        }
            
        if (strcmp(operation, "R") == 0) {
            excludedPokemon = removal();
            printf("(R) %s\n", excludedPokemon->name);
        }

        free(operation);
    }

    displayInformation();

    free(pokemons);

    return 0;
}