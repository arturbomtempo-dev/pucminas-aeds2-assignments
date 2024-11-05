#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

/**
 * TP03Q05 - Lista com Alocação Flexível em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 05/11/2024
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
void removeOccurrences(char *str, char caractere) {
    int i, j = 0;
    size_t comprimento = strlen(str);
    
    for (i = 0; i < comprimento; i++) {
        if (str[i] != caractere) {
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
    Pokemon *pokemons = (Pokemon *)malloc (801 * sizeof(Pokemon));

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

        char *stringAbilities = removeAttribute(&token, ','); 

        removeOccurrences(stringAbilities, '[');
        removeOccurrences(stringAbilities, ']');
        removeOccurrences(stringAbilities, '\'');

        char *tokenAbilities = stringAbilities;
        int indexAbility = 0;

        while (*tokenAbilities != '\0' && indexAbility < 10) {
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
                strcpy(temp->abilities[indexAbility], startAbility);
                indexAbility++;
                tokenAbilities = endAbility + 1;
            } else {
                strcpy(temp->abilities[indexAbility], startAbility);
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
 * Estrutura que representa uma célula individual em uma lista encadeada.
 * Cada célula armazena um Pokémon e um ponteiro para a próxima célula,
 * permitindo a conexão entre os elementos da lista.
 */
struct Cell {
    Pokemon *pokemon;
    struct Cell *next;
} typedef Cell;

/**
 * Estrutura que representa a lista encadeada de Pokémons.
 * Contém ponteiros para a primeira e última células da lista,
 * facilitando a inserção e remoção de elementos, e um contador
 * para o tamanho da lista.
 */
struct List {
    struct Cell *first, *last;
    int size;
} typedef List;

/**
 * Cria uma nova célula na lista encadeada para armazenar um Pokémon.
 * Aloca espaço na memória para uma nova célula, define o Pokémon
 * especificado e inicializa o ponteiro da próxima célula como NULL.
 *
 * @param pokemon Ponteiro para o Pokémon que será armazenado na célula.
 * @return Ponteiro para a nova célula criada.
 */
Cell *newCell(Pokemon *pokemon) {
    Cell *temp = (Cell *) malloc (sizeof(Cell));
    temp->pokemon = pokemon;
    temp->next = NULL;
    return temp;
}

/**
 * Cria e inicializa uma nova lista encadeada.
 * Define o primeiro e o último elemento da lista como uma célula vazia,
 * e inicializa o tamanho da lista como zero.
 *
 * @return Estrutura List inicializada com uma célula vazia.
 */
List newList() {
    List temp;
    temp.first = temp.last = newCell(NULL);
    temp.size = 0;

    return temp;
}

/**
 * Insere um novo Pokémon no início da lista.
 * Cria uma nova célula com o Pokémon fornecido, liga essa célula ao
 * primeiro elemento atual da lista e redefine o primeiro elemento da lista.
 * Incrementa o tamanho da lista.
 *
 * @param list Ponteiro para a lista onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido no início da lista.
 */
void insertStart(List *list, Pokemon *pokemon) {
    Cell *temp = newCell(pokemon);
    temp->next = list->first;

    list->first->pokemon = pokemon;

    list->first = temp;
    list->size++;
}

/**
 * Insere um novo Pokémon no final da lista.
 * Cria uma nova célula com o Pokémon fornecido, liga essa célula ao
 * último elemento atual da lista e redefine o último elemento da lista.
 * Incrementa o tamanho da lista.
 *
 * @param list Ponteiro para a lista onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido no final da lista.
 */
void insertEnd(List *list, Pokemon *pokemon) {
    list->last->next = newCell(pokemon);
    list->last = list->last->next;
    list->size++;
}

/**
 * Insere um Pokémon em uma posição específica da lista.
 * Dependendo da posição especificada, o Pokémon pode ser inserido no início, 
 * no final ou em uma posição intermediária da lista. Se a posição é inválida,
 * uma mensagem de erro é exibida.
 *
 * @param list Ponteiro para a lista onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido na lista.
 * @param position A posição na lista onde o Pokémon deve ser inserido.
 *                 Se for 0, insere no início; se for igual ao tamanho da lista, insere no final.
 */
void insert(List *list, Pokemon *pokemon, int position) {
    if (position < 0 || position > list->size) {
        printf("Erro ao tentar inserir na posição (%d/ tamanho = %d) inválida.", position, list->size);
    } else if (position == 0) {
        insertStart(list, pokemon);
    } else if (position == list->size) {
        insertEnd(list, pokemon);
    } else {
        Cell *previous = list->first;

        for (int i = 0; i < position; i++) {
            previous = previous->next;
        }

        Cell *temp = newCell(pokemon);
        temp->next = previous->next;
        previous->next = temp;
        list->size++;
    }
}

/**
 * Remove um Pokémon da lista em uma posição específica. 
 * Caso a lista esteja vazia ou a posição seja inválida, exibe uma mensagem de erro.
 * Se a remoção for bem-sucedida, retorna o Pokémon removido.
 *
 * @param list Ponteiro para a lista de onde o Pokémon será removido.
 * @param position A posição da lista de onde o Pokémon deve ser removido.
 *                 Se for 0, remove o primeiro elemento; se for igual ao tamanho da lista - 1, remove o último.
 * @return Um ponteiro para o Pokémon removido, ou NULL se a lista estiver vazia ou a posição for inválida.
 */
Pokemon *removal(List *list, int position) {
    if (list->first == list->last) {
        printf("\nA list está vazia!\n");
        return NULL;
    } else if (position < 0 || position >= list->size) {
        printf("Erro ao tentar remover item da posição (%d / tamanho = %d) inválida.\n", position, list->size);
        return NULL;
    } else {
        Cell *previous = list->first;

        for (int i = 0; i < position; i++) {
            previous = previous->next;
        }

        Cell *temp = previous->next;
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
 * Remove o primeiro Pokémon da lista.
 * 
 * @param list Ponteiro para a lista de onde o Pokémon será removido.
 * @return Um ponteiro para o Pokémon removido do início da lista, ou NULL se a lista estiver vazia.
 */
Pokemon *removeStart(List *list) {
    return removal(list, 0);
}

/**
 * Remove o último Pokémon da lista.
 * 
 * @param list Ponteiro para a lista de onde o Pokémon será removido.
 * @return Um ponteiro para o Pokémon removido do final da lista, ou NULL se a lista estiver vazia.
 */
Pokemon *removeEnd(List *list) {
    return removal(list, list->size-1);
}

/**
 * Exibe todos os Pokémon na lista.
 * 
 * @param list Ponteiro para a lista a ser exibida.
 */
void showList(List *list) {
    Cell *i;
    int count = 0;

    for (i = list->first->next; i != NULL; i = i->next) {
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
            i->pokemon->captureDate.ano);
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
 * Função principal que executa a lógica do programa.
 * 
 * Esta função lê os dados dos Pokémon de um arquivo CSV, insere Pokémon em uma lista com base nas operações fornecidas pelo usuário,
 * e exibe a lista após as operações de inserção e remoção. 
 * As operações suportadas incluem inserção no início, inserção no final, remoção do início, remoção do final, 
 * inserção em uma posição específica e remoção de uma posição específica.
 */
int main() {
    Pokemon* pokemons = readCsv("/tmp/pokemon.csv");

    List pokemonsList = newList();

    char input[30];
    int id;
    
    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);

        insertEnd(&pokemonsList, search(pokemons, id));
    }

    int numberOperations = 0;

    Pokemon *deletedPokemons[50];
    int k = 0;

    scanf("%d", &numberOperations);

    for (int j = 0; j < numberOperations; j++) {
        char* operation = (char *) malloc(sizeof(char) * 3);
        scanf("%s", operation);

        if (strcmp(operation, "II") == 0) {
            int number;
            scanf("%d", &number);
            insertStart(&pokemonsList, search(pokemons, number));
        }
            
        if (strcmp(operation, "IF") == 0) {
            int number;
            scanf("%d", &number);
            insertEnd(&pokemonsList, search(pokemons, number));
        }
            
        if (strcmp(operation, "RI") == 0) {
            deletedPokemons[k++] = removeStart(&pokemonsList);
        }
            
        if (strcmp(operation, "RF") == 0) {
            deletedPokemons[k++] = removeEnd(&pokemonsList);
        }
            
        if (strcmp(operation, "I*") == 0) {
            int position;
            scanf("%d", &position);
            int number;
            scanf("%d", &number);
            insert(&pokemonsList, search(pokemons, number), position);
        }
            
        if (strcmp(operation, "R*") == 0) {
            int position;
            scanf("%d", &position);
            deletedPokemons[k++] = removal(&pokemonsList, position);
        }

        free(operation);
    }

    for (int i = 0; i < k; i++) {
        printf("(R) %s\n", deletedPokemons[i]->name);
    }

    showList(&pokemonsList);

    free(pokemons);

    return 0;
}