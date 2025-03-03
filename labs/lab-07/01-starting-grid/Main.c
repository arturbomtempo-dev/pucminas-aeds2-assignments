#include <stdio.h>

/**
 * LAB07 - Grid de Largada
 *
 * @author Artur Bomtempo Colen
 * @version 1.0, 11/10/2024
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

int countInversions(int arr[], int n) {
    int temp[n];
    return mergeSortAndCount(arr, temp, 0, n - 1);
}

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
 *    devido ao uso do Merge Sort, que divide a lista em sublistas menores e as
 * mescla.
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