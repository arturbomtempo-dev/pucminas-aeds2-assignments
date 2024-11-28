#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/**
 * TP04Q03 - Árvore AVL
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 28/11/2024
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
 * Representa um nó de uma árvore, contendo um objeto Pokemon, ponteiros para os filhos
 * esquerdo e direito, e o nível do nó na árvore.
 */
struct Node {
    Pokemon *pokemon;
    struct Node *left, *right;
    int level;
} typedef Node;

/**
 * Cria e inicializa um nó com os valores fornecidos.
 *
 * @param pokemon Ponteiro para o objeto Pokemon a ser armazenado no nó.
 * @param left Ponteiro para o nó filho à esquerda.
 * @param right Ponteiro para o nó filho à direita.
 * @param level Nível do nó na árvore.
 * @return Ponteiro para o nó recém-criado.
 */
Node *setNode(Pokemon *pokemon, Node *left, Node *right, int level) {
    Node *temp = (Node *) malloc(sizeof(Node));

    temp->pokemon = pokemon;
    temp->right = right;
    temp->left = left;
    temp->level = level;

    movements += 3;

    return temp;
}

/**
 * Cria um novo nó com filhos nulos e nível inicial igual a 1.
 *
 * @param pokemon Ponteiro para o objeto Pokemon a ser armazenado no nó.
 * @return Ponteiro para o novo nó criado.
 */
Node *newNode(Pokemon *pokemon) {
    return setNode(pokemon, NULL, NULL, 1);
}

/**
 * Retorna o nível de um nó da árvore.
 *
 * @param node Ponteiro para o nó cujo nível será retornado.
 * @return O nível do nó ou 0 caso o nó seja nulo.
 */
int getLevel(Node *node) {
    return (node == NULL) ? 0 : node->level;
}

/**
 * Define o nível de um nó com base nos níveis de seus filhos.
 *
 * @param node Ponteiro para o nó cujo nível será atualizado.
 */
void setLevel(Node *node) {
    if (node != NULL) {
        node->level = 1 + (getLevel(node->left) > getLevel(node->right) ? getLevel(node->left) : getLevel(node->right));
    }
}

Node* root;

/**
 * Inicializa a raiz da árvore, definindo-a como nula.
 */
void start() {
    root = NULL;
}

/**
 * Realiza a busca recursiva por um Pokémon pelo nome na árvore binária.
 *
 * @param name Nome do Pokémon a ser buscado.
 * @param i Ponteiro para o nó atual na recursão.
 * @return `true` se o Pokémon foi encontrado; caso contrário, `false`.
 */
bool recursiveSearch(char *name, Node* i) {
    bool found;

    if (i == NULL) {
        found = false;
    } else if (strcmp(name, i->pokemon->name) == 0) {
        comparisons++;
        found = true;
    } else if (strcmp(name, i->pokemon->name) < 0) {
        comparisons++;
        printf("esq ");
        found = recursiveSearch(name, i->left);
    } else {
        comparisons+=2;
        printf("dir ");
        found = recursiveSearch(name, i->right);
    }

    return found;
}

/**
 * Inicia a busca por um Pokémon na árvore, exibindo o caminho percorrido.
 *
 * @param name Nome do Pokémon a ser buscado.
 * @return `true` se o Pokémon foi encontrado; caso contrário, `false`.
 */
bool seacrh(char *name) {
    printf("%s\n",name);
    printf("raiz ");
    return recursiveSearch(name, root);
}

/**
 * Realiza uma rotação para a direita no nó fornecido.
 *
 * @param node Ponteiro para o nó que será rotacionado.
 * @return Ponteiro para o novo nó raiz após a rotação.
 */
Node* rotateRight(Node *node) {
    Node *leftNode = node->left;
    Node *leftRightNode = leftNode->right;

    leftNode->right = node;
    node->left = leftRightNode;

    setLevel(node);
    setLevel(leftNode);

    movements += 4;

    return leftNode;
}

/**
 * Realiza uma rotação para a esquerda no nó fornecido.
 *
 * @param node Ponteiro para o nó que será rotacionado.
 * @return Ponteiro para o novo nó raiz após a rotação.
 */
Node* rotateLeft(Node *node) {
    Node *rightNode = node->right;
    Node *rightLeftNode = rightNode->left;

    rightNode->left = node;
    node->right = rightLeftNode;

    setLevel(node);
    setLevel(rightNode);

    movements += 4;

    return rightNode;
}

/**
 * Realiza o balanceamento do nó especificado na árvore AVL.
 *
 * @param node Ponteiro para o nó a ser balanceado.
 * @return Ponteiro para o nó balanceado (pode ser o mesmo nó ou um novo após rotações).
 *
 * @details
 * - Calcula o fator de balanceamento do nó.
 * - Realiza rotações simples ou duplas (direita ou esquerda) conforme necessário para manter a propriedade AVL.
 * - Exibe um erro e encerra a execução se o fator de balanceamento for inválido.
 */
Node* balance(Node *node) {
    if (node != NULL) {
        int factor = getLevel(node->right) - getLevel(node->left);

        if (factor >= -1 && factor <= 1) {
            setLevel(node);
        } else if (factor == 2) {
            int sonRightFactor = getLevel(node->right->right) - getLevel(node->right->left);

			if (sonRightFactor == -1) {
				node->right = rotateRight(node->right);
			}

            node = rotateLeft(node);
        } else if (factor == -2) {
            int sonLeftFactor = getLevel(node->left->right) - getLevel(node->left->left);

            if (sonLeftFactor == 1) {
                node->left = rotateLeft(node->left);
            }

            node = rotateRight(node);
        } else {
            printf("Erro no No(%s) com fator de balanceamento (%d) inválido.", node->pokemon->name, factor);
            exit(0);
        }
    }

    return node;
}

/**
 * Insere um novo Pokémon na árvore AVL de forma recursiva.
 *
 * @param pokemon Ponteiro para o Pokémon a ser inserido.
 * @param i Ponteiro para o nó atual da árvore onde a inserção será avaliada.
 * @return Ponteiro para o nó após a inserção e balanceamento.
 */
Node* recursiveInsert(Pokemon *pokemon, Node* i) {
    if (i == NULL) {
        i = newNode(pokemon);
    } else if (strcmp(pokemon->name, i->pokemon->name) < 0) {
        i->left = recursiveInsert(pokemon, i->left);
    } else if (strcmp(pokemon->name, i->pokemon->name) > 0) {
        i->right = recursiveInsert(pokemon, i->right);
    } else {
        printf("Erro ao insirir.");
        exit(0);
    }

    return balance(i);
}

/**
 * Insere um novo Pokémon na árvore AVL.
 *
 * @param pokemon Ponteiro para o Pokémon a ser inserido.
 */
void insert(Pokemon *pokemon) {
    root = recursiveInsert(pokemon, root);
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
 * Função principal que controla o fluxo de execução do programa.
 *
 * @return `0` ao finalizar a execução com sucesso.
 *
 * @details
 * - Lê os dados dos Pokémon a partir de um arquivo CSV.
 * - Inicializa a estrutura de árvore AVL.
 * - Insere os Pokémon na árvore com base nos IDs fornecidos na entrada padrão.
 * - Realiza buscas na árvore com base nos nomes fornecidos na entrada padrão.
 * - Mede o tempo de execução total e salva os resultados em um arquivo.
 * - Libera a memória alocada para os dados dos Pokémon.
 */
int main() {
    clock_t startClock, endClock;
    double totalTime;

    Pokemon *pokemons = readCsv("/tmp/pokemon.csv");

    start();

    char input[30];
    int id;

    startClock = clock();
    
    while (scanf("%s", input) && !isEnd(input)) {
        sscanf(input, "%d", &id);
        insert(search(pokemons, id));
    }

    while (scanf("%s", input) && !isEnd(input)) {
        bool found = seacrh(input);
        printf("%s\n", found ? "SIM" : "NAO");
    }

    endClock = clock();
    totalTime = ((double)(endClock - startClock));

    saveExecutionFile("847235_avl.txt", totalTime);

    free(pokemons);

    return 0;
}