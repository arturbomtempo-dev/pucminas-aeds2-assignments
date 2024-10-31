#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * TP03Q02 - Lista com Alocação Sequencial em C
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 30/10/2024
 */

/**
 * Estrutura que representa uma data, composta por dia, mês e ano.
 */
struct Date {
    int day;
    int month;
    int year;
} typedef Date;

/**
 * Estrutura que representa um Pokémon, com suas características gerais,
 * incluindo identificador, geração, nome, descrição, tipos, habilidades,
 * peso, altura, taxa de captura, se é lendário e data de captura.
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
 * Estrutura que representa uma lista de Pokémons, contendo um ponteiro para 
 * os Pokémons e o número de elementos na lista.
 */
struct List {
    Pokemon **pokemons;
    int number;
} typedef List;

/**
 * Converte uma string em formato de data para uma estrutura Date.
 * 
 * @param str A string contendo a data no formato "dia/mês/ano".
 * @return Uma estrutura Date com o dia, mês e ano extraídos da string;
 *         retorna 0 em cada campo se a string for nula ou vazia.
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
 * Converte uma estrutura Date em uma string formatada.
 * 
 * @param date A estrutura Date contendo o dia, mês e ano a serem formatados.
 * @return Uma string no formato "dd/mm/aaaa" representando a data; 
 *         a string é alocada dinamicamente e deve ser liberada pelo chamador.
 */
char *dateToString(Date date) {
    char *str = (char*) malloc (11 * sizeof(char));
    sprintf(str, "%02d/%02d/%04d", date.day, date.month, date.year);
    return str;
}

/**
 * Retorna o identificador único do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return O identificador do Pokémon.
 */
int getId(Pokemon *p) {
    return p->id;
}


/**
 * Define o identificador único do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param id Novo identificador do Pokémon.
 */
void setId(Pokemon *p, int id) {
    p->id = id;
}

/**
 * Retorna a geração do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return A geração do Pokémon.
 */
int getGeneration(Pokemon *p) {
    return p->generation;
}

/**
 * Define a geração do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param generation Nova geração do Pokémon.
 */
void setGeneration(Pokemon *p, int generation) {
    p->generation = generation;
}

/**
 * Retorna o nome do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return O nome do Pokémon.
 */
char *getName(Pokemon *p) {
    return p->name;
}


/**
 * Define o nome do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param name Novo nome do Pokémon.
 */
void setName(Pokemon *p, char *name) {
    p->name = name;
}

/**
 * Retorna a descrição do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return A descrição do Pokémon.
 */
char *getDescription(Pokemon *p) {
    return p->description;
}

/**
 * Define a descrição do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param description Nova descrição do Pokémon.
 */
void setDescription(Pokemon *p, char *description) {
    p->description = description;
}


/**
 * Retorna o tipo do Pokémon em uma posição específica.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param index Índice do tipo (0 ou 1).
 * @return O tipo do Pokémon na posição especificada.
 */
char *getTypes(Pokemon *p, int index) {
    return p->types[index];
}


/**
 * Retorna o número de tipos atribuídos ao Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return O número de tipos do Pokémon.
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
 * Define o tipo do Pokémon em uma posição específica.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param index Índice do tipo (0 ou 1).
 * @param type Novo tipo do Pokémon.
 */
void setTypes(Pokemon *p, int index, char *type) {
    strncpy(p->types[index], type, sizeof(p->types[index]) - 1);
    p->types[index][sizeof(p->types[index]) - 1] = '\0';
}

/**
 * Retorna a habilidade do Pokémon em uma posição específica.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param index Índice da habilidade (0 a 5).
 * @return A habilidade do Pokémon na posição especificada.
 */
char *getAbilities(Pokemon *p, int index) {
    return p->abilities[index];
}

/**
 * Retorna o número de habilidades atribuídas ao Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return O número de habilidades do Pokémon.
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
 * Define a habilidade do Pokémon em uma posição específica.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param index Índice da habilidade (0 a 5).
 * @param ability Nova habilidade do Pokémon.
 */
void setAbilities(Pokemon *p, int index, const char *ability) {
    strncpy(p->abilities[index], ability, sizeof(p->abilities[index]) - 1);
    p->abilities[index][sizeof(p->abilities[index]) - 1] = '\0';
}

/**
 * Retorna o peso do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return O peso do Pokémon.
 */
double getWeight(Pokemon *p) {
    return p->weight;
}

/**
 * Define o peso do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param weight Novo peso do Pokémon.
 */
void setWeight(Pokemon *p, double weight) {
    p->weight = weight;
}


/**
 * Retorna a altura do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return A altura do Pokémon.
 */
double getHeight(Pokemon *p) {
    return p->height;
}

/**
 * Define a altura do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param height Nova altura do Pokémon.
 */
void setHeight(Pokemon *p, double height) {
    p->height = height;
}

/**
 * Retorna a taxa de captura do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return A taxa de captura do Pokémon.
 */
int getCaptureRate(Pokemon *p) {
    return p->captureRate;
}

/**
 * Define a taxa de captura do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param captureRate Nova taxa de captura do Pokémon.
 */
void setCaptureRate(Pokemon *p, int captureRate) {
    p->captureRate = captureRate;
}

/**
 * Retorna se o Pokémon é lendário.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return Verdadeiro se o Pokémon é lendário, falso caso contrário.
 */
bool getIsLegendary(Pokemon *p) {
    return p->isLegendary;
}

/**
 * Define se o Pokémon é lendário.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param isLegendary Novo status lendário do Pokémon.
 */
void setIsLegendary(Pokemon *p, bool isLegendary) {
    p->isLegendary = isLegendary;
}


/**
 * Retorna a data de captura do Pokémon.
 * 
 * @param p Ponteiro para o Pokémon.
 * @return A data de captura do Pokémon.
 */
Date getCaptureDate(Pokemon *p) {
    return p->captureDate;
}

/**
 * Define a data de captura do Pokémon a partir de uma estrutura Date.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param captureDate Nova data de captura do Pokémon.
 */
void setCaptureDate(Pokemon *p, Date captureDate) {
    p->captureDate = captureDate;
}

/**
 * Define a data de captura do Pokémon a partir de uma string.
 * 
 * @param p Ponteiro para o Pokémon.
 * @param captureDate String representando a nova data de captura no formato "dd/mm/aaaa".
 */
void setCaptureDateString(Pokemon *p, char *captureDate) {
    p->captureDate = stringToDate(captureDate);
}

/**
 * Cria e inicializa um novo Pokémon com os atributos fornecidos.
 * 
 * @param id Identificador único do Pokémon.
 * @param generation Geração à qual o Pokémon pertence.
 * @param name Nome do Pokémon.
 * @param description Descrição detalhada do Pokémon.
 * @param type1 Primeiro tipo do Pokémon.
 * @param type2 Segundo tipo do Pokémon, ou NULL se não houver.
 * @param abilities Array de habilidades do Pokémon (até 6 habilidades).
 * @param weight Peso do Pokémon em quilogramas.
 * @param height Altura do Pokémon em metros.
 * @param captureRate Taxa de captura do Pokémon.
 * @param isLegendary Indica se o Pokémon é lendário.
 * @param captureDate Data de captura do Pokémon.
 * @return Uma estrutura Pokemon inicializada com os atributos especificados.
 */
Pokemon createPokemon(int id, int generation, char *name, char *description, char *type1, char *type2, char *abilities[6], double weight, double height, int captureRate, bool isLegendary, Date captureDate) {
    Pokemon pokemon;

    setId(&pokemon, id);
    setGeneration(&pokemon, generation);

    char *nameCopy = strdup(name);
    char *descriptionCopy = strdup(description);

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
 * Divide uma linha CSV em campos, considerando campos entre aspas como um único campo.
 * 
 * @param line Linha de texto CSV a ser dividida.
 * @param fields Array de ponteiros para armazenar os campos extraídos.
 * @param max_fields Número máximo de campos a serem extraídos.
 * @return O número de campos extraídos da linha.
 */
int splitCsvLine(char *line, char **fields, int max_fields) {
    int fieldCount = 0;
    char *ptr = line;
    int inQuotes = 0;
    char *fieldStart = ptr;

    while (*ptr && fieldCount < max_fields) {
        if (*ptr == '"') {
            inQuotes = !inQuotes;
        } else if (*ptr == ',' && !inQuotes) {
            *ptr = '\0';
            fields[fieldCount++] = fieldStart;
            fieldStart = ptr + 1;
        }

        ptr++;
    }

    if (fieldCount < max_fields) {
        fields[fieldCount++] = fieldStart;
    }

    return fieldCount;
}

/**
 * Lê um arquivo CSV e preenche um array de estruturas Pokémon com os dados extraídos.
 * 
 * @param file Ponteiro para o arquivo CSV a ser lido.
 * @param pokemons Array onde os Pokémons extraídos serão armazenados.
 * @param n Ponteiro para o número atual de Pokémons no array, que será atualizado.
 */
void readCsv(FILE *file, Pokemon *pokemons, int *n) {
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
        pokemon.name = strdup(fields[2]);
        pokemon.description = strdup(fields[3]);
        
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
        
        pokemons[*n] = pokemon;
        (*n)++;
    }
}

/**
 * Exibe as informações detalhadas de um Pokémon em formato legível.
 * 
 * @param p Ponteiro para a estrutura Pokémon cujas informações devem ser exibidas.
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

    printf("'] - ");

    int numberAbilities = getNumberAbilities(p);

    printf("[");

    for (int i = 0; i < numberAbilities; i++) {
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

    free(data);

    printf("\n");
}

/**
 * Compara duas datas e determina sua ordem relativa.
 * 
 * @param date1 Ponteiro para a primeira data a ser comparada.
 * @param date2 Ponteiro para a segunda data a ser comparada.
 * @return Um valor negativo se date1 for anterior a date2, 
 *         um valor positivo se date1 for posterior a date2,
 *         ou zero se ambas as datas forem iguais.
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
 * Busca um Pokémon pelo seu identificador único em um array de Pokémons.
 * 
 * @param pokemons Array de estruturas Pokémon onde a busca será realizada.
 * @param n Número total de Pokémons no array.
 * @param id Identificador único do Pokémon a ser encontrado.
 * @return Um ponteiro para o Pokémon encontrado, ou NULL se nenhum Pokémon com o ID especificado for encontrado.
 */
Pokemon *findPokemonById(Pokemon pokemons[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (pokemons[i].id == id) {
            return &pokemons[i];
        }
    }

    return NULL;
}

/**
 * Inicializa uma lista de Pokémons com uma quantidade especificada.
 * 
 * @param quantity Número máximo de Pokémons que a lista pode conter.
 * @return Uma estrutura List inicializada, pronta para armazenar Pokémons.
 */
List initializeList(int quantity) {
    List list;

	list.pokemons = malloc (quantity * sizeof(Pokemon*));
	list.number = 0;

	return list;
}

/**
 * Insere um Pokémon em uma posição específica na lista.
 * 
 * @param list Ponteiro para a lista onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido na lista.
 * @param position Posição na qual o Pokémon será inserido. 
 *                 Deve ser um valor válido entre 0 e o número atual de Pokémons na lista.
 *                 Se a lista estiver cheia ou a posição for inválida, uma mensagem de erro será exibida.
 */
void insert(List *list, Pokemon *pokemon, int position) {
    if (list->number >= 100 || position < 0 || position > list->number) {
        printf("Erro: Posição inválida ou lista cheia.\n");
    }

    for (int i = list->number; i > position; i--) {
        list->pokemons[i] = list->pokemons[i - 1];
    }

    list->pokemons[position] = pokemon;
    list->number++;
}

/**
 * Insere um Pokémon no início da lista.
 * 
 * @param list Ponteiro para a lista onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido na lista.
 */
void insertStart(List *list, Pokemon *pokemon) {
    insert(list, pokemon, 0);
}

/**
 * Insere um Pokémon no final da lista.
 * 
 * @param list Ponteiro para a lista onde o Pokémon será inserido.
 * @param pokemon Ponteiro para o Pokémon a ser inserido na lista.
 */
void insertEnd(List *list, Pokemon *pokemon) {
    insert(list, pokemon, list->number);
}

/**
 * Remove um Pokémon de uma posição específica na lista.
 * 
 * @param list Ponteiro para a lista da qual o Pokémon será removido.
 * @param position Posição do Pokémon a ser removido. Deve ser um valor válido entre 0 e o número atual de Pokémons na lista.
 * @return Ponteiro para o Pokémon removido da lista.
 * @throws exit(EXIT_FAILURE) Se a lista estiver vazia ou a posição for inválida.
 */
Pokemon *removal(List *list, int position) {
    if (list->number == 0 || position < 0 || position >= list->number) {
        printf("Erro: Posição inválida ou lista vazia.\n");
        exit(EXIT_FAILURE);
    }

    Pokemon *removedPokemon = list->pokemons[position];

    for (int i = position; i < list->number - 1; i++) {
        list->pokemons[i] = list->pokemons[i + 1];
    }

    list->number--;

    return removedPokemon;
}

/**
 * Remove o Pokémon do início da lista.
 * 
 * @param list Ponteiro para a lista da qual o Pokémon será removido.
 * @return Ponteiro para o Pokémon removido do início da lista.
 */
Pokemon *removalStart(List *list) {
    return removal(list, 0);
}

/**
 * Remove o Pokémon do final da lista.
 * 
 * @param list Ponteiro para a lista da qual o Pokémon será removido.
 * @return Ponteiro para o Pokémon removido do final da lista.
 */
Pokemon *removalEnd(List *list) {
    return removal(list, (list->number) - 1);
}

/**
 * Imprime todos os Pokémons contidos na lista.
 * 
 * @param list Ponteiro para a lista que contém os Pokémons a serem impressos.
 */
void printList(List *list) {
    for (int i = 0; i < list->number; i++) {
        printf("[%d] ", i);
        displayInformation(list->pokemons[i]);
    }
}

/**
 * Função principal do programa que lê dados de um arquivo CSV contendo informações sobre Pokémons
 * e gerencia uma lista de Pokémons baseada em comandos de entrada do usuário.
 */
int main() {
    FILE *file = fopen("/tmp/pokemon.csv", "r");   

    if (file == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
    } 

    Pokemon pokemons[801];
    int n = 0;

    readCsv(file, pokemons, &n);

    fclose(file);

    List pokemonList = initializeList(100);

    char inputId[10];

    scanf("%s", inputId);
    
    while (strcmp(inputId, "FIM") != 0) {
        int id = atoi(inputId);
        Pokemon *p = findPokemonById(pokemons, n, id);

        if (p != NULL) {
            insertEnd(&pokemonList, p);
        }
        
        scanf("%s", inputId); 
    }

    int commandsQuantity;
    char commands[3];

    scanf("%i", &commandsQuantity);

    for (int i = 0; i < commandsQuantity; i++) {
        scanf("%s", commands);

        if (strcmp(commands, "II") == 0) {
            scanf("%s", inputId);

            int id = atoi(inputId);
            Pokemon *pokemon = findPokemonById(pokemons, n, id);

            if (pokemon != NULL) {
                insertStart(&pokemonList, pokemon);
            }
        } else if (strcmp(commands, "I*") == 0) {
            int position;

            scanf("%d", &position);
            scanf("%s", inputId); 

            int id = atoi(inputId);
            Pokemon *pokemon = findPokemonById(pokemons, n, id);

            if (pokemon != NULL) {
                insert(&pokemonList, pokemon, position);
            }
        } else if (strcmp(commands, "IF") == 0) {
            scanf("%s", inputId);

            int id = atoi(inputId);
            Pokemon *pokemon = findPokemonById(pokemons, n, id);

            if (pokemon != NULL) {
                insertEnd(&pokemonList, pokemon);
            }
        } else if (strcmp(commands, "RI") == 0) {
            Pokemon *pokemon = removalStart(&pokemonList);

            if (pokemon != NULL) {
                printf("(R) %s\n", pokemon->name);
            }
        } else if (strcmp(commands, "R*") == 0) {
            int position;

            scanf("%d", &position);

            Pokemon *pokemon = removal(&pokemonList, position);

            if (pokemon != NULL) {
                printf("(R) %s\n", pokemon->name);
            }
        } else if (strcmp(commands, "RF") == 0) {
            Pokemon *pokemon = removalEnd(&pokemonList);

            if (pokemon != NULL) {
                printf("(R) %s\n", pokemon->name);
            }
        }
    }

    printList(&pokemonList);
 
    for (int i = 0; i < n; i++) {
        free(pokemons[i].name);
        free(pokemons[i].description);
    }

    return 0;
}