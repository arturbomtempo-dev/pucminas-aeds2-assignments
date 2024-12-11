#include <stdio.h>
#include <string.h>

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