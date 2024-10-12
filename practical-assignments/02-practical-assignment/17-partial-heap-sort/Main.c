#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * TP02Q17 - Heapsort PARCIAL
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 12/10/2024
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
    char *name;
    char *description;
    char types[2][50];
    char abilities[6][50];
    double weight;
    double height;
    int captureRate;
    bool isLegendary;
    Date captureDate;
} typedef Pokemon;

/**
 * A função utiliza `sscanf` para extrair o dia, mês e ano da string fornecida. Caso a string 
 * seja inválida, os valores da data são inicializados como zero.
 * 
 * @param str Uma string representando uma data no formato "DD/MM/AAAA".
 * @return Uma estrutura Date contendo os valores do dia, mês e ano extraídos da string.
 *         Se a string for inválida (nula ou vazia), os campos da data serão inicializados com zero.
 */
Date stringToDate(char *str) {
    Date date;

    if (str != NULL && strlen(str) > 0) {
        sscanf(str, "%d/%d/%d", &date.day, &date.month, &date.year);
    } else {
        date.day = 0;
        date.month = 0;
        date.year = 0;
    }

    return date;
}

/**
 * A função formata uma estrutura Date para uma string no formato "DD/MM/AAAA", alocando 
 * dinamicamente a memória necessária para armazenar a string resultante.
 * 
 * @param date Uma estrutura Date contendo o dia, mês e ano que serão formatados.
 * @return Um ponteiro para a string formatada contendo a data no formato "DD/MM/AAAA".
 *         A memória para a string é alocada dinamicamente e deve ser liberada após o uso.
 */
char *dateToString(Date date) {
    char *str = (char *)malloc(11 * sizeof(char));

    sprintf(str, "%02d/%02d/%04d", date.day, date.month, date.year);

    return str;
}

/**
 * A função aloca memória dinamicamente e faz uma cópia da string fornecida, retornando um ponteiro 
 * para a nova string. Caso a alocação falhe, retorna NULL.
 * 
 * @param s A string original que será duplicada.
 * @return Um ponteiro para a nova string copiada. Retorna NULL se a alocação de memória falhar.
 */
char* strdupFunction(const char* s) {
    char* copy = (char*)malloc(strlen(s) + 1);

    if (copy != NULL) {
        strcpy(copy, s);
    }

    return copy;
}

/**
 * A função retorna o ID do Pokémon fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual o ID será obtido.
 * @return O ID do Pokémon.
 */
int getId(Pokemon *p) {
    return p->id;
}

/**
 * A função define o ID do Pokémon para o valor fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá seu ID atualizado.
 * @param id O novo ID a ser atribuído ao Pokémon.
 */
void setId(Pokemon *p, int id) {
    p->id = id;
}

/**
 * A função retorna a geração do Pokémon fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual a geração será obtida.
 * @return A geração do Pokémon.
 */
int getGeneration(Pokemon *p) {
    return p->generation;
}

/**
 * A função define a geração do Pokémon para o valor fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá sua geração atualizada.
 * @param generation O novo valor da geração a ser atribuído ao Pokémon.
 */
void setGeneration(Pokemon *p, int generation) {
    p->generation = generation;
}

/**
 * A função retorna o nome do Pokémon fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual o nome será obtido.
 * @return Um ponteiro para a string contendo o nome do Pokémon.
 */
char* getName(Pokemon *p) {
    return p->name;
}

/**
 * A função define o nome do Pokémon para a string fornecida.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá seu nome atualizado.
 * @param name Um ponteiro para a string contendo o novo nome a ser atribuído ao Pokémon.
 */
void setName(Pokemon *p, char *name) {
    p->name = name;
}

/**
 * A função retorna a descrição do Pokémon fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual a descrição será obtida.
 * @return Um ponteiro para a string contendo a descrição do Pokémon.
 */
char* getDescription(Pokemon *p) {
    return p->description;
}

/**
 * A função define a descrição do Pokémon para a string fornecida.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá sua descrição atualizada.
 * @param description Um ponteiro para a string contendo a nova descrição a ser atribuída ao Pokémon.
 */
void setDescription(Pokemon *p, char *description) {
    p->description = description;
}

/**
 * A função retorna o tipo do Pokémon no índice fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual o tipo será obtido.
 * @param index O índice do array de tipos do Pokémon a ser retornado.
 * @return Um ponteiro para a string contendo o tipo do Pokémon no índice fornecido.
 */
char* getTypes(Pokemon *p, int index) {
    return p->types[index];
}

/**
 * A função retorna o número de tipos válidos (não vazios) que o Pokémon possui.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual o número de tipos será contado.
 * @return O número de tipos válidos do Pokémon (máximo 2).
 */
int getNumberTypes(Pokemon *p) {
    int count = 0;

    for (int i = 0; i < 2; i++) {
        if (strlen(p->types[i]) > 0) {
            count++;
        }
    }

    return count;
}

/**
 * A função define o tipo do Pokémon no índice fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá o tipo atualizado.
 * @param index O índice do array de tipos a ser atualizado.
 * @param type Um ponteiro para a string contendo o tipo a ser atribuído ao Pokémon no índice fornecido.
 */
void setTypes(Pokemon *p, int index, char *type) {
    strncpy(p->types[index], type, sizeof(p->types[index]) - 1);
    p->types[index][sizeof(p->types[index]) - 1] = '\0';
}

/**
 * A função retorna a habilidade do Pokémon no índice fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual a habilidade será obtida.
 * @param index O índice do array de habilidades do Pokémon a ser retornado.
 * @return Um ponteiro para a string contendo a habilidade do Pokémon no índice fornecido.
 */
char* getAbilities(Pokemon *p, int index) {
    return p->abilities[index];
}

/**
 * A função retorna o número de habilidades válidas (não vazias) que o Pokémon possui.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual o número de habilidades será contado.
 * @return O número de habilidades válidas do Pokémon (máximo 6).
 */
int getNumberAbilities(Pokemon *p) {
    int count = 0;

    for (int i = 0; i < 6; i++) {
        if (strlen(p->abilities[i]) > 0) {
            count++;
        }
    }

    return count;
}

/**
 * A função define a habilidade do Pokémon no índice fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá a habilidade atualizada.
 * @param index O índice do array de habilidades a ser atualizado.
 * @param ability Um ponteiro para a string contendo a habilidade a ser atribuída ao Pokémon no índice fornecido.
 */
void setAbilities(Pokemon *p, int index, const char *ability) {
    strncpy(p->abilities[index], ability, sizeof(p->abilities[index]) - 1);
    p->abilities[index][sizeof(p->abilities[index]) - 1] = '\0';
}

/**
 * A função retorna o peso do Pokémon.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual o peso será obtido.
 * @return O peso do Pokémon.
 */
double getWeight(Pokemon *p) {
    return p->weight;
}

/**
 * A função define o peso do Pokémon para o valor fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá o peso atualizado.
 * @param weight O novo valor do peso a ser atribuído ao Pokémon.
 */
void setWeight(Pokemon *p, double weight) {
    p->weight = weight;
}

/**
 * A função retorna a altura do Pokémon.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual a altura será obtida.
 * @return A altura do Pokémon.
 */
double getHeight(Pokemon *p) {
    return p->height;
}

/**
 * A função define a altura do Pokémon para o valor fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá a altura atualizada.
 * @param height O novo valor da altura a ser atribuído ao Pokémon.
 */
void setHeight(Pokemon *p, double height) {
    p->height = height;
}

/**
 * A função retorna a taxa de captura do Pokémon.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual a taxa de captura será obtida.
 * @return A taxa de captura do Pokémon.
 */
int getCaptureRate(Pokemon *p) {
    return p->captureRate;
}

/**
 * A função define a taxa de captura do Pokémon para o valor fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá a taxa de captura atualizada.
 * @param captureRate O novo valor da taxa de captura a ser atribuído ao Pokémon.
 */
void setCaptureRate(Pokemon *p, int captureRate) {
    p->captureRate = captureRate;
}

/**
 * A função retorna se o Pokémon é lendário ou não.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual o status lendário será obtido.
 * @return Um valor booleano indicando se o Pokémon é lendário (true) ou não (false).
 */
bool getIsLegendary(Pokemon *p) {
    return p->isLegendary;
}

/**
 * A função define se o Pokémon é lendário ou não.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá o status lendário atualizado.
 * @param isLegendary Um valor booleano indicando se o Pokémon é lendário (true) ou não (false).
 */
void setIsLegendary(Pokemon *p, bool isLegendary) {
    p->isLegendary = isLegendary;
}

/**
 * A função retorna a data de captura do Pokémon.
 * 
 * @param p Um ponteiro para a estrutura Pokémon da qual a data de captura será obtida.
 * @return Uma estrutura Date contendo a data de captura do Pokémon.
 */
Date getCaptureDate(Pokemon *p) {
    return p->captureDate;
}

/**
 * A função define a data de captura do Pokémon para o valor fornecido.
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá a data de captura atualizada.
 * @param captureDate Uma estrutura Date contendo a nova data de captura do Pokémon.
 */
void setCaptureDate(Pokemon *p, Date captureDate) {
    p->captureDate = captureDate;
}

/**
 * A função define a data de captura do Pokémon com base em uma string fornecida no formato "DD/MM/AAAA".
 * 
 * @param p Um ponteiro para a estrutura Pokémon que terá a data de captura atualizada.
 * @param captureDate Uma string representando a nova data de captura no formato "DD/MM/AAAA".
 */
void setCaptureDateString(Pokemon *p, char *captureDate) {
    p->captureDate = stringToDate(captureDate);
}

/**
 * A função cria uma nova instância da estrutura Pokémon, inicializando seus campos com os valores fornecidos.
 * 
 * @param id O identificador único do Pokémon.
 * @param generation A geração à qual o Pokémon pertence.
 * @param name O nome do Pokémon.
 * @param description Uma descrição do Pokémon.
 * @param type1 O primeiro tipo do Pokémon.
 * @param type2 O segundo tipo do Pokémon (pode ser nulo).
 * @param abilities Um array de strings contendo as habilidades do Pokémon.
 * @param weight O peso do Pokémon.
 * @param height A altura do Pokémon.
 * @param captureRate A taxa de captura do Pokémon.
 * @param isLegendary Um valor booleano indicando se o Pokémon é lendário.
 * @param captureDate A data de captura do Pokémon.
 * @return Uma nova instância da estrutura Pokémon, com todos os campos inicializados conforme os parâmetros fornecidos.
 */
Pokemon createPokemon(int id, int generation, char *name, char *description, char *type1, char *type2, char *abilities[6], double weight, double height, int captureRate, bool isLegendary, Date captureDate) {
    Pokemon pokemon;

    setId(&pokemon, id);
    setGeneration(&pokemon, generation);

    char *nameCopy = strdupFunction(name);
    char *descriptionCopy = strdupFunction(description);

    setName(&pokemon, nameCopy);
    setDescription(&pokemon, descriptionCopy);
    setTypes(&pokemon, 0, type1);

    if (type2 != NULL) {
        setTypes(&pokemon, 1, type2);
    }

    for (int i = 0; i < 6; i++) {
        if (abilities[i] != NULL) {
            setAbilities(&pokemon, i, abilities[i]);
        } else {
            strcpy(pokemon.abilities[i], "");
        }
    }

    setWeight(&pokemon, weight);
    setHeight(&pokemon, height);
    setCaptureRate(&pokemon, captureRate);
    setIsLegendary(&pokemon, isLegendary);
    setCaptureDate(&pokemon, captureDate);

    return pokemon;
}

/**
 * A função divide uma linha CSV em campos, considerando as aspas que podem conter vírgulas.
 * 
 * @param line A linha CSV a ser dividida em campos.
 * @param fields Um array de strings onde os campos extraídos serão armazenados.
 * @param max_fields O número máximo de campos que podem ser armazenados no array.
 * @return O número total de campos extraídos da linha.
 */
int splitCsvLine(char *line, char **fields, int max_fields) {
    int fieldCount = 0;
    char *pointer = line;
    int inQuotes = 0;
    char *fieldStart = pointer;

    while (*pointer && fieldCount < max_fields) {
        if (*pointer == '"') {
            inQuotes = !inQuotes;
        } else if (*pointer == ',' && !inQuotes) {
            *pointer = '\0';
            fields[fieldCount++] = fieldStart;
            fieldStart = pointer + 1;
        }

        pointer++;
    }

    if (fieldCount < max_fields) {
        fields[fieldCount++] = fieldStart;
    }

    return fieldCount;
}

/**
 * A função lê dados de Pokémon a partir de um arquivo CSV e os armazena em um array de Pokémon.
 * Cada linha do arquivo é processada para extrair as informações do Pokémon, incluindo id, 
 * geração, nome, descrição, tipos, habilidades, peso, altura, taxa de captura, se é lendário 
 * e a data de captura. Os dados são adicionados ao array de Pokédex, e o contador de Pokémon 
 * é atualizado.
 * 
 * @param file O ponteiro para o arquivo CSV a ser lido.
 * @param pokedex O array onde os Pokémon extraídos do arquivo serão armazenados.
 * @param n Um ponteiro para um inteiro que representa o número atual de Pokémon no pokédex.
 *          Este valor será atualizado após a leitura.
 */
void readCsv(FILE *file, Pokemon *pokedex, int *n) {
    char line[1024];

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        Pokemon pokemon;

        memset(&pokemon, 0, sizeof(Pokemon));

        char *fields[12];
        int fieldCount = splitCsvLine(line, fields, 12);

        pokemon.id = atoi(fields[0]);
        pokemon.generation = atoi(fields[1]);
        pokemon.name = strdupFunction(fields[2]);
        pokemon.description = strdupFunction(fields[3]);

        setTypes(&pokemon, 0, fields[4]);

        if (strlen(fields[5]) > 0) {
            setTypes(&pokemon, 1, fields[5]);
        } else {
            strcpy(pokemon.types[1], "");
        }

        char *abilitiesField = fields[6];

        if (abilitiesField[0] == '"' && abilitiesField[strlen(abilitiesField) - 1] == '"') {
            abilitiesField[strlen(abilitiesField) - 1] = '\0';
            abilitiesField++;
        }
        if (abilitiesField[0] == '[' && abilitiesField[strlen(abilitiesField) - 1] == ']') {
            abilitiesField[strlen(abilitiesField) - 1] = '\0';
            abilitiesField++;
        }

        char *abilityToken;
        char *restAbilities = abilitiesField;
        int abilityIndex = 0;

        while ((abilityToken = strtok_r(restAbilities, ",", &restAbilities)) && abilityIndex < 6) {
            while (*abilityToken == ' ' || *abilityToken == '\'') {
                abilityToken++;
            }

            char *tempEnd = abilityToken + strlen(abilityToken) - 1;

            while (tempEnd > abilityToken && (*tempEnd == ' ' || *tempEnd == '\'')) {
                *tempEnd = '\0';
                tempEnd--;
            }
            
            if (strlen(abilityToken) > 0) {
                setAbilities(&pokemon, abilityIndex, abilityToken);
                abilityIndex++;
            }
        }

        for (; abilityIndex < 6; abilityIndex++) {
            strcpy(pokemon.abilities[abilityIndex], "");
        }

        pokemon.weight = atof(fields[7]);
        pokemon.height = atof(fields[8]);
        pokemon.captureRate = atoi(fields[9]);
        pokemon.isLegendary = atoi(fields[10]);
        pokemon.captureDate = stringToDate(fields[11]);
        
        pokedex[*n] = pokemon;
        (*n)++;
    }
}

/**
 * A função exibe as informações de um Pokémon formatadas em uma string, incluindo id, nome, 
 * descrição, tipos, habilidades, peso, altura, taxa de captura, se é lendário, geração e 
 * data de captura. As informações são impressas no console no formato especificado.
 * 
 * @param p Um ponteiro para a estrutura Pokémon cujas informações serão exibidas.
 */
void displayInformation(Pokemon *p) {
    printf("[#%d -> %s: %s - ['", getId(p), getName(p), getDescription(p));

    int numberTypes = getNumberTypes(p);

    if (numberTypes > 0) {
        printf("%s", getTypes(p, 0));
    }

    if (numberTypes > 1) {
        printf("', '%s", getTypes(p, 1));
    }

    printf("'] - [");

    int numberAbilities = getNumberAbilities(p);

    for (int i = 0 ; i < numberAbilities ; i++) {
        printf("'%s'", getAbilities(p, i));

        if (i < numberAbilities - 1) {
            printf(", ");
        }
    }

    printf("] - ");

    printf("%.1fkg - ", getWeight(p));
    printf("%.1fm - ", getHeight(p));
    printf("%d%% - ", getCaptureRate(p));
    printf("%s - ", getIsLegendary(p) ? "true" : "false");
    printf("%d gen] - ", getGeneration(p));

    char *data = dateToString(getCaptureDate(p));

    printf("%s", data);

    printf("\n");

    free(data);
}

/**
 * A função compara duas datas, retornando um valor negativo se a primeira data 
 * é anterior à segunda, um valor positivo se é posterior, e zero se são iguais.
 * 
 * @param date1 Um ponteiro para a primeira estrutura Date a ser comparada.
 * @param date2 Um ponteiro para a segunda estrutura Date a ser comparada.
 * @return Um inteiro indicando a ordem das datas: negativo se date1 < date2, 
 *         positivo se date1 > date2, e zero se date1 == date2.
 */
int compareDates(Date *date1, Date *date2) {
    if (date1->year != date2->year) {
        return date1->year - date2->year;
    }

    if (date1->month != date2->month) {
        return date1->month - date2->month;
    }

    return date1->day - date2->day;
}

/**
 * A função troca dois elementos do tipo Pokemon, utilizando uma variável auxiliar
 * para armazenar temporariamente um dos elementos durante a troca.
 * 
 * @param a Um ponteiro para o primeiro Pokemon a ser trocado.
 * @param b Um ponteiro para o segundo Pokemon a ser trocado.
 */
void swap(Pokemon *a, Pokemon *b) {
    Pokemon aux = *a;

    *a = *b;
    *b = aux;
}

/**
 * A função `heapify` reorganiza um subárvore de um heap, garantindo que a 
 * propriedade do heap seja mantida. Ela compara o nó atual com seus filhos 
 * e, se necessário, realiza trocas para garantir que o maior elemento 
 * esteja na raiz da subárvore. É usada como parte do algoritmo de 
 * ordenação heapsort.
 * 
 * @param heap O vetor que representa o heap.
 * @param n O número total de elementos no heap.
 * @param i O índice do nó atual a ser verificado.
 * @param comparisons Um ponteiro para a variável que conta as comparações realizadas.
 * @param movements Um ponteiro para a variável que conta as movimentações realizadas.
 */
void heapify(Pokemon heap[], int n, int i, int *comparisons, int *movements) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n) {
        (*comparisons)++;

        if ((heap[left].height > heap[largest].height) || ((heap[left].height == heap[largest].height) && (strcmp(heap[left].name, heap[largest].name) > 0))) {
            largest = left;
        }
    }

    if (right < n) {
        (*comparisons)++;

        if ((heap[right].height > heap[largest].height) || ((heap[right].height == heap[largest].height) && (strcmp(heap[right].name, heap[largest].name) > 0))) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        (*movements)++;

        heapify(heap, n, largest, comparisons, movements);
    }
}

/**
 * A função `buildHeap` constrói um heap a partir de um vetor de 
 * elementos. Ela inicia do último nó pai e chama a função 
 * `heapify` para cada nó pai, garantindo que a estrutura do heap 
 * seja mantida. Isso é um passo crucial na implementação do algoritmo 
 * de ordenação heapsort.
 * 
 * @param heap O vetor que representa o heap a ser construído.
 * @param n O número total de elementos no heap.
 * @param comparisons Um ponteiro para a variável que conta as comparações realizadas.
 * @param movements Um ponteiro para a variável que conta as movimentações realizadas.
 */
void buildHeap(Pokemon heap[], int n, int *comparisons, int *movements) {
    int startIndex = (n / 2) - 1;

    for (int i = startIndex; i >= 0; i--) {
        heapify(heap, n, i, comparisons, movements);
    }
}

/**
 * A função `partialHeapSort` realiza uma ordenação parcial dos 
 * elementos de um vetor de Pokémon utilizando o algoritmo heapsort. 
 * Ela mantém um heap de tamanho k, inserindo novos elementos conforme 
 * necessário e garantindo que apenas os k Pokémon com menor altura 
 * sejam mantidos no heap.
 * 
 * @param findPokemon O vetor de Pokémon a ser ordenado parcialmente.
 * @param n O número total de elementos no vetor.
 * @param k O número de elementos que devem ser mantidos no vetor final.
 * @param comparisons Um ponteiro para a variável que conta as comparações realizadas.
 * @param movements Um ponteiro para a variável que conta as movimentações realizadas.
 */
void partialHeapSort(Pokemon findPokemon[], int n, int k, int *comparisons, int *movements) {
    Pokemon heap[k];

    for (int i = 0 ; i < k ; i++) {
        heap[i] = findPokemon[i];
        (*movements)++;
    }

    buildHeap(heap, k, comparisons, movements);

    for (int i = k ; i < n ; i++) {
        (*comparisons)++;

        if ((findPokemon[i].height < heap[0].height) || ((findPokemon[i].height == heap[0].height) && (strcmp(findPokemon[i].name, heap[0].name)< 0))) {
            heap[0] = findPokemon[i];


            (*movements)++;
            heapify(heap, k, 0, comparisons, movements);
        }
    }

    for (int i = k - 1; i >= 0; i--) {
        findPokemon[i] = heap[0];

        (*movements)++;

        heap[0] = heap[i];

        (*movements)++;

        heapify(heap, i, 0, comparisons, movements);
    }
}

/**
 * Função principal que executa o programa.
 * 
 * Esta função lê um arquivo CSV contendo dados de Pokémon, 
 * permite que o usuário insira IDs de Pokémon para procurar,
 * e utiliza o algoritmo de ordenação HeapSort para exibir os Pokémon 
 * encontrados com base em critérios definidos.
 */
int main() {
    clock_t start = clock();

    FILE *file = fopen("/tmp/pokemon.csv", "r");   

    if (file == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return 1;
    } 

    Pokemon pokedex[801];
    int n = 0;

    readCsv(file, pokedex, &n);

    fclose(file);

    char inputId[10];
    scanf("%s", inputId);

    Pokemon findPokemon[51];
    int comparisons = 0;
    int movements = 0;
    int j = 0;
    
    while (strcmp(inputId, "FIM") != 0) {
        int id = atoi(inputId);

        for (int i = 0 ; i < n ; i++) {
            if (pokedex[i].id == id) {
                findPokemon[j++] = pokedex[i];
                break;
            }
        }
        
        scanf("%s", inputId); 
    }

    int k = 10;

    partialHeapSort(findPokemon, j, k, &comparisons, &movements);

    for (int i = 0 ; i < k ; i++) {
        displayInformation(&findPokemon[i]);
    }

    clock_t end = clock();
    double executionTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

    FILE *archive = fopen("847235_partialHeapSort.txt", "w");

    if (archive == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(archive, "847235\t%d\t%d\t%.2f\n", comparisons, movements, executionTime);

    fclose(archive);

    for (int i = 0; i < n; i++) {
        free(pokedex[i].name);
        free(pokedex[i].description);
    }

    return 0;
}