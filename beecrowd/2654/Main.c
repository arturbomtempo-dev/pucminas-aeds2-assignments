#include <stdio.h>
#include <string.h>

/**
 * BEE 2654
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 11/12/2024
 */

typedef struct Character {
    char name[101];
    int powerLevel;
    int godsKilled;
    int deaths;
} Character;


int main() {
    int N;
    scanf("%d", &N);
    Character chosen;

    strcpy(chosen.name, "");
    chosen.powerLevel = -1;
    chosen.godsKilled = -1;
    chosen.deaths = 101;

    for (int i = 0; i < N; i++) {
        Character character;
        scanf("%s %d %d %d", character.name, &character.powerLevel, &character.godsKilled, &character.deaths);

        if (
            character.powerLevel > chosen.powerLevel ||
            (character.powerLevel == chosen.powerLevel && character.godsKilled > chosen.godsKilled) ||
            (character.powerLevel == chosen.powerLevel && character.godsKilled == chosen.godsKilled && character.deaths < chosen.deaths) ||
            (character.powerLevel == chosen.powerLevel && character.godsKilled == chosen.godsKilled && character.deaths == chosen.deaths && strcmp(character.name, chosen.name) < 0)
        ) {
            strcpy(chosen.name, character.name);
            chosen.powerLevel = character.powerLevel;
            chosen.godsKilled = character.godsKilled;
            chosen.deaths = character.deaths;
        }
    }

    printf("%s\n", chosen.name);

    return 0;
}