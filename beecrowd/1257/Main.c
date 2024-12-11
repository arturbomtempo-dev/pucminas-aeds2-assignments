#include <stdio.h>
#include <string.h>

/**
 * BEE 1257
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 10/12/2024
 */

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int hash = 0;
        int L;
        scanf("%d", &L);
        getchar();

        for (int j = 0; j < L; j++) {
            char expression[51];
            scanf("%s", expression);
            
            for (int k = 0; k < strlen(expression); k++) {
                int letterPosition = expression[k] - 'A';
                int expressionValue = letterPosition + j + k;
                hash += expressionValue;
            }
        }

        printf("%d\n", hash);
    }

    return 0;
}