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

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef struct Pokemon {
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
} Pokemon;

Pokemon* search(Pokemon *pokemons, int id) {
    Pokemon *pokemon;
    
    for (int i = 0; i < 801; i++) {
        if (pokemons[i].id == id) {
            pokemon = &pokemons[i];
        }
    }
    
    return pokemon; 
}

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

void saveExecutionFile(const char *Filename, long totalTime) {
    FILE *file = fopen(Filename, "w+");

    if (file == NULL) {
        printf("Erro ao gerar o arquivo.\n");
    } else {
        fprintf(file, "847235\t%d\t%d\t%ldms", comparisons, movements, totalTime);
        fclose(file);
    }
}

typedef struct Node {
    Pokemon *pokemon;
    struct Node *left, *right;
    int level;
} Node;

Node *setNode(Pokemon *pokemon, Node *left, Node *right, int level) {
    Node *temp = (Node *) malloc(sizeof(Node));

    temp->pokemon = pokemon;
    temp->right = right;
    temp->left = left;
    temp->level = level;

    movements += 3;

    return temp;
}

Node *newNode(Pokemon *pokemon) {
    return setNode(pokemon, NULL, NULL, 1);
}

int getLevel(Node *node) {
    return (node == NULL) ? 0 : node->level;
}

void setLevel(Node *node) {
    if (node != NULL) {
        node->level = 1 + (getLevel(node->left) > getLevel(node->right) ? getLevel(node->left) : getLevel(node->right));
    }
}

Node* root;

void start() {
    root = NULL;
}

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

bool seacrh(char *name) {
    printf("%s\n",name);
    printf("raiz ");
    return recursiveSearch(name, root);
}

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

void insert(Pokemon *pokemon) {
    root = recursiveInsert(pokemon, root);
}

bool isEnd(char* input) {
    return (strlen(input) == 3 && input[0] == 'F' && input[1] == 'I' && input[2] == 'M');
}

int main() {
    clock_t startClock, endClock;
    double totalTime;

    Pokemon *pokemons = readCsv("../tmp/pokemon.csv");

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