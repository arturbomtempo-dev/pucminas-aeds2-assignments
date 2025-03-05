#include <stdio.h>
#include <stdlib.h>

/**
 * Código fonte - Implementação da Matriz Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Flexible Matrix
 * @language C
 * @version 1.0
 */

typedef struct Cell {
    int element;
    struct Cell *bottom, *top, *left, *right;
} Cell;

typedef struct Matrix {
    Cell *start;
    int row, column;
} Matrix;

Cell *newCell(int element) {
    Cell *new = (Cell *)malloc(sizeof(Cell));
    new->element = element;
    new->bottom = new->top = new->left = new->right = NULL;
    return new;
}

Matrix *createMatrix(int row, int column) {
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->row = row;
    matrix->column = column;

    matrix->start = newCell(0);
    Cell *current = matrix->start;

    for (int i = 0; i < row; i++) {
        Cell *temp = current;

        for (int j = 1; j < column; j++) {
            Cell *newCellRight = newCell(0);
            temp->right = newCellRight;
            newCellRight->left = temp;
            temp = newCellRight;
        }

        if (i < row - 1) {
            Cell *newCellBottom = newCell(0);
            current->bottom = newCellBottom;
            newCellBottom->top = current;
            current = newCellBottom;
        }
    }

    for (Cell *row = matrix->start; row->bottom != NULL; row = row->bottom) {
        Cell *colTop = row;
        Cell *colBottom = row->bottom;

        while (colTop != NULL) {
            colTop->bottom = colBottom;
            colBottom->top = colTop;
            colTop = colTop->right;
            colBottom = colBottom->right;
        }
    }

    return matrix;
}

void readMatrix(Matrix *matrix) {
    Cell *currentRow = matrix->start;

    for (int i = 0; i < matrix->row; i++) {
        Cell *currentCol = currentRow;

        for (int j = 0; j < matrix->column; j++) {
            printf("Digite o valor para a célula [%d][%d]: ", i, j);
            scanf("%d", &currentCol->element);
            currentCol = currentCol->right;
        }

        currentRow = currentRow->bottom;
    }
}

void printMatrix(Matrix *matrix) {
    Cell *currentRow = matrix->start;

    for (int i = 0; i < matrix->row; i++) {
        Cell *currentCol = currentRow;

        for (int j = 0; j < matrix->column; j++) {
            printf("%d ", currentCol->element);
            currentCol = currentCol->right;
        }

        printf("\n");
        currentRow = currentRow->bottom;
    }
}

Matrix *sumMatrix(Matrix *m1, Matrix *m2) {
    if (m1->row != m2->row || m1->column != m2->column) {
        printf("Dimensões incompatíveis para soma.\n");
        return NULL;
    }

    Matrix *result = createMatrix(m1->row, m1->column);
    Cell *rowA = m1->start, *rowB = m2->start, *rowC = result->start;

    for (int i = 0; i < m1->row; i++) {
        Cell *a = rowA, *b = rowB, *c = rowC;
        for (int j = 0; j < m1->column; j++) {
            c->element = a->element + b->element;
            a = a->right;
            b = b->right;
            c = c->right;
        }
        rowA = rowA->bottom;
        rowB = rowB->bottom;
        rowC = rowC->bottom;
    }

    return result;
}

Matrix *multiplyMatrix(Matrix *m1, Matrix *m2) {
    if (m1->column != m2->row) {
        printf("Dimensões incompatíveis para multiplicação.\n");
        return NULL;
    }

    Matrix *result = createMatrix(m1->row, m2->column);
    Cell *rowA = m1->start;
    Cell *rowC = result->start;

    for (int i = 0; i < m1->row; i++) {
        Cell *colBStart = m2->start;
        Cell *currentC = rowC;

        for (int j = 0; j < m2->column; j++) {
            Cell *a = rowA;
            Cell *b = colBStart;
            int sum = 0;

            for (int k = 0; k < m1->column; k++) {
                sum += a->element * b->element;
                a = a->right;
                b = b->bottom;
            }
            currentC->element = sum;
            currentC = currentC->right;
            colBStart = colBStart->right;
        }

        rowA = rowA->bottom;
        rowC = rowC->bottom;
    }

    return result;
}

int isSquareMatrix(Matrix *matrix) { return matrix->row == matrix->column; }

void freeMatrix(Matrix *matrix) {
    Cell *currentRow = matrix->start;

    while (currentRow != NULL) {
        Cell *currentCol = currentRow;
        currentRow = currentRow->bottom;

        while (currentCol != NULL) {
            Cell *temp = currentCol;
            currentCol = currentCol->right;
            free(temp);
        }
    }

    free(matrix);
}

int main() {
    int rows, cols;

    printf("Digite o número de linhas: ");
    scanf("%d", &rows);

    printf("Digite o número de colunas: ");
    scanf("%d", &cols);

    Matrix *matrix1 = createMatrix(rows, cols);

    printf("Preencha os valores da primeira matriz:\n");
    readMatrix(matrix1);

    Matrix *matrix2 = createMatrix(rows, cols);

    printf("Preencha os valores da segunda matriz:\n");
    readMatrix(matrix2);

    printf("Matriz 1:\n");
    printMatrix(matrix1);
    printf("Matriz 2:\n");
    printMatrix(matrix2);

    Matrix *sumResult = sumMatrix(matrix1, matrix2);

    if (sumResult != NULL) {
        printf("Resultado da soma:\n");
        printMatrix(sumResult);
    }

    if (isSquareMatrix(matrix1)) {
        printf("A primeira matriz é quadrada.\n");
    } else {
        printf("A primeira matriz não é quadrada.\n");
    }

    freeMatrix(matrix1);
    freeMatrix(matrix2);

    if (sumResult != NULL) {
        freeMatrix(sumResult);
    }

    return 0;
}