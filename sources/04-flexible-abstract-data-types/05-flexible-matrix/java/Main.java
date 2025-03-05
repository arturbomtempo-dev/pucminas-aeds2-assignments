import java.util.Scanner;

/**
 * Código fonte - Implementação da Matriz Flexível
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Flexible Matrix
 * @language Java
 * @version 1.0
 */

class Cell {
    public int element;
    public Cell bottom, top, left, right;

    public Cell() {
        this(0);
    }

    public Cell(int element) {
        this(element, null, null, null, null);
    }

    public Cell(int element, Cell bottom, Cell top, Cell left, Cell right) {
        this.element = element;
        this.bottom = bottom;
        this.top = top;
        this.left = left;
        this.right = right;
    }
}

class Matrix {
    private Cell start;
    private int row, column;

    public Matrix() {
        this(3, 3);
    }

    public Matrix(int row, int column) {
        this.row = row;
        this.column = column;
        allocateMatrix();
    }

    private void allocateMatrix() {
        start = new Cell();
        Cell current = start;

        for (int i = 0; i < row; i++) {
            Cell temp = current;

            for (int j = 1; j < column; j++) {
                Cell newCell = new Cell();
                temp.right = newCell;
                newCell.left = temp;
                temp = newCell;
            }

            if (i < row - 1) {
                Cell newRow = new Cell();
                current.bottom = newRow;
                newRow.top = current;
                current = newRow;
            }
        }

        for (Cell currentRow = start; currentRow.bottom != null; currentRow = currentRow.bottom) {
            Cell currentColumn = currentRow;
            Cell bottomColumn = currentRow.bottom;

            while (currentColumn != null) {
                currentColumn.bottom = bottomColumn;
                bottomColumn.top = currentColumn;
                currentColumn = currentColumn.right;
                bottomColumn = bottomColumn.right;
            }
        }
    }

    public void read(Scanner sc) {
        Cell currentRow = start;

        for (int i = 0; i < row; i++) {
            Cell currentColumn = currentRow;

            for (int j = 0; j < column; j++) {
                System.out.print("Digite o valor para a célula [" + i + "][" + j + "]: ");
                currentColumn.element = sc.nextInt();
                currentColumn = currentColumn.right;
            }

            currentRow = currentRow.bottom;
        }
    }

    public void print() {
        Cell currentRow = start;

        for (int i = 0; i < row; i++) {
            Cell currentColumn = currentRow;

            for (int j = 0; j < column; j++) {
                System.out.print(currentColumn.element + " ");
                currentColumn = currentColumn.right;
            }

            System.out.println();
            currentRow = currentRow.bottom;
        }
    }

    public Matrix sum(Matrix m) {
        Matrix response = null;

        if (this.row == m.row && this.column == m.column) {
            response = new Matrix(this.row, this.column);
            Cell rowA = this.start;
            Cell rowB = m.start;
            Cell rowC = response.start;

            for (int i = 0; i < row; i++) {
                Cell a = rowA;
                Cell b = rowB;
                Cell c = rowC;

                for (int j = 0; j < column; j++) {
                    c.element = a.element + b.element;
                    a = a.right;
                    b = b.right;
                    c = c.right;
                }

                rowA = rowA.bottom;
                rowB = rowB.bottom;
                rowC = rowC.bottom;
            }
        }

        return response;
    }

    public Matrix multiplication(Matrix m) {
        Matrix response = null;

        if (this.column == m.row) {
            response = new Matrix(this.row, m.column);

            Cell rowA = this.start;
            Cell rowC = response.start;

            for (int i = 0; i < this.row; i++) {
                Cell columnB = m.start;
                Cell CellC = rowC;

                for (int j = 0; j < m.column; j++) {
                    int sum = 0;
                    Cell a = rowA;
                    Cell b = columnB;

                    for (int k = 0; k < this.column; k++) {
                        sum += a.element * b.element;
                        a = a.right;
                        b = b.bottom;
                    }

                    CellC.element = sum;
                    CellC = CellC.right;
                    columnB = columnB.right;
                }

                rowA = rowA.bottom;
                rowC = rowC.bottom;
            }
        }

        return response;
    }

    public boolean isSquare() {
        return this.row == this.column;
    }

    public void showMainDiagonal() {
        if (isSquare()) {
            Cell current = start;

            for (int i = 0; i < row; i++) {
                System.out.print(current.element + " ");
                current = current.bottom != null ? current.bottom.right : null;
            }

            System.out.println();
        }
    }

    public void showSecondDiagonal() {
        if (isSquare()) {
            Cell current = start;

            for (int i = 0; i < row - 1; i++) {
                current = current.right;
            }

            for (int i = 0; i < row; i++) {
                System.out.print(current.element + " ");
                current = current.bottom != null ? current.bottom.left : null;
            }

            System.out.println();
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Digite o número de linhas (M1): ");
        int rowsM1 = sc.nextInt();
        System.out.print("Digite o número de colunas (M1): ");
        int columnsM1 = sc.nextInt();
        Matrix m1 = new Matrix(rowsM1, columnsM1);

        System.out.print("Digite o número de linhas (M2): ");
        int rowsM2 = sc.nextInt();
        System.out.print("Digite o número de colunas (M2): ");
        int columnsM2 = sc.nextInt();
        Matrix m2 = new Matrix(rowsM2, columnsM2);

        System.out.print("Digite o número de linhas (M3): ");
        int rowsM3 = sc.nextInt();
        System.out.print("Digite o número de colunas (M3): ");
        int columnsM3 = sc.nextInt();
        Matrix m3 = new Matrix(rowsM3, columnsM3);

        System.out.print("Digite o número de linhas (M4): ");
        int rowsM4 = sc.nextInt();
        System.out.print("Digite o número de colunas (M4): ");
        int columnsM4 = sc.nextInt();
        Matrix m4 = new Matrix(rowsM4, columnsM4);

        System.out.println("Preencha os valores da matriz M1:");
        m1.read(sc);
        System.out.println("Preencha os valores da matriz M2:");
        m2.read(sc);
        System.out.println("Preencha os valores da matriz M3:");
        m3.read(sc);
        System.out.println("Preencha os valores da matriz M4:");
        m4.read(sc);

        System.out.println("Resultado da soma de M1 e M2:");

        Matrix sum = m1.sum(m2);

        if (sum != null) {
            sum.print();
        } else {
            System.out.println("Não é possível somar as matrizes M1 e M2 (dimensões incompatíveis).");
        }

        System.out.println("Resultado da multiplicação de M3 e M4:");
        Matrix multiplication = m3.multiplication(m4);

        if (multiplication != null) {
            multiplication.print();
        } else {
            System.out.println("Não é possível multiplicar as matrizes M3 e M4 (dimensões incompatíveis).");
        }

        if (m1.isSquare()) {
            System.out.println("Diagonal Principal de M1:");
            m1.showMainDiagonal();

            System.out.println("Diagonal Secundária de M1:");
            m1.showSecondDiagonal();
        } else {
            System.out.println("M1 não é uma matriz quadrada; não possui diagonais principais ou secundárias.");
        }

        sc.close();
    }
}