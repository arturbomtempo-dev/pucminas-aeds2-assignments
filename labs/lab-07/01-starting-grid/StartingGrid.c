#include <stdio.h>

/**
 * LAB07 - Grid de Largada
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 11/10/2024
 */

/**
 * A função compara elementos das duas sublistas (esquerda e direita) e os mescla em um único array ordenado. 
 * Durante a mesclagem, ela conta quantas vezes um elemento da sublista direita é menor que um elemento da 
 * sublista esquerda, o que indica uma inversão. As inversões são contadas e retornadas, permitindo que o 
 * algoritmo que utiliza essa função mantenha um registro do número total de inversões no array original.
 * 
 * @param arr O array original que contém os elementos a serem mesclados.
 * @param temp Um array temporário utilizado para armazenar a mesclagem dos elementos.
 * @param left O índice inicial da sublista à esquerda.
 * @param mid O índice médio que divide as duas sublistas.
 * @param right O índice final da sublista à direita.
 * @return O número de inversões encontradas durante a mesclagem.
 */
int mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    int invCount = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return invCount;
}

/**
 * A função divide recursivamente o array em duas metades até que cada sublista tenha um único elemento, 
 * em seguida, mescla essas sublistas de volta em um array ordenado enquanto conta as inversões. 
 * Uma inversão é uma condição em que um elemento maior precede um elemento menor no array. 
 * O número total de inversões é retornado, permitindo a análise do grau de desordem do array original.
 * 
 * @param arr O array que contém os elementos a serem ordenados.
 * @param temp Um array temporário utilizado para armazenar os elementos durante o processo de mesclagem.
 * @param left O índice inicial da sublista a ser ordenada.
 * @param right O índice final da sublista a ser ordenada.
 * @return O número total de inversões encontradas no array.
 */
int mergeSortAndCount(int arr[], int temp[], int left, int right) {
    int mid, invCount = 0;

    if (left < right) {
        mid = (left + right) / 2;

        invCount += mergeSortAndCount(arr, temp, left, mid);
        invCount += mergeSortAndCount(arr, temp, mid + 1, right);
        invCount += mergeAndCount(arr, temp, left, mid, right);
    }

    return invCount;
}

/**
 * A função cria um array temporário para auxiliar na ordenação e na contagem das inversões. 
 * Em seguida, chama a função `mergeSortAndCount` para realizar a ordenação do array e contabilizar 
 * as inversões simultaneamente. Uma inversão é definida como uma situação em que um elemento maior 
 * precede um elemento menor no array. O valor retornado representa o total de tais condições no 
 * array original, permitindo uma análise do grau de desordem do conjunto de dados.
 * 
 * @param arr O array cujos elementos devem ser analisados para contagem de inversões.
 * @param n O número de elementos no array.
 * @return O número total de inversões encontradas no array.
 */
int countInversions(int arr[], int n) {
    int temp[n];
    return mergeSortAndCount(arr, temp, 0, n - 1);
}

/**
 * Função principal que lê a quantidade de intervalos, as horas de início e de término 
 * desses intervalos, e calcula o número de inversões entre os intervalos de término 
 * em relação aos intervalos de início.
 */
int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        int start[N], finish[N];

        for (int i = 0; i < N; i++) {
            scanf("%d", &start[i]);
        }

        for (int i = 0; i < N; i++) {
            scanf("%d", &finish[i]);
        }

        int position[N + 1];

        for (int j = 0; j < N; j++) {
            position[start[j]] = j;
        }

        int mapped[N];

        for (int i = 0; i < N; i++) {
            mapped[i] = position[finish[i]];
        }

        int inversions = countInversions(mapped, N);
        printf("%d\n", inversions);
    }

    return 0;
}

/*
 * Análise de Complexidade:
 * 
 * 1. O tempo de execução do algoritmo de contagem de inversões é O(N log N)
 *    devido ao uso do Merge Sort, que divide a lista em sublistas menores e as mescla.
 * 
 * 2. A contagem de inversões é feita durante o processo de mesclagem, onde
 *    cada inversão é contabilizada em O(1).
 * 
 * 3. No total, a complexidade de tempo do algoritmo é dominada pela operação
 *    de ordenação, resultando em O(N log N).
 * 
 * 4. A complexidade espacial é O(N) devido ao vetor temporário usado durante
 *    a mesclagem.
 */