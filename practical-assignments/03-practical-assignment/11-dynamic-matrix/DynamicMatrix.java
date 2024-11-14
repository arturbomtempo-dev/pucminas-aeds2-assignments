import java.util.Scanner;

/**
 * TP03Q11 - Matriz Dinâmica em Java
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 14/11/2024
 */

/**
 * Classe que representa uma célula de uma matriz flexível,
 * com referências para as células vizinhas em todas as direções.
 */
class Cell {
    public int element;
    public Cell bottom, top, left, right;

    /**
     * Construtor padrão que inicializa o elemento com valor zero e as células 
     * adjacentes como nulas.
     */
    public Cell() {
        this(0);
    }

    /**
     * Construtor que inicializa o elemento com um valor específico e as células 
     * adjacentes como nulas.
     *
     * @param element Valor do elemento a ser armazenado na célula
     */
    public Cell(int element) {
        this(element, null, null, null, null);
    }

    /**
     * Construtor que inicializa o elemento e define as referências das células adjacentes.
     *
     * @param element Valor do elemento a ser armazenado na célula
     * @param bottom Referência para a célula abaixo
     * @param top Referência para a célula acima
     * @param left Referência para a célula à esquerda
     * @param right Referência para a célula à direita
     */
    public Cell(int element, Cell bottom, Cell top, Cell left, Cell right) {
        this.element = element;
        this.bottom = bottom;
        this.top = top;
        this.left = left;
        this.right = right;
    }
}

/**
 * Classe que representa uma matriz com células ligadas entre si,
 * permitindo operações de soma e multiplicação de matrizes.
 */
class Matrix {
    private Cell start;
    private int row, column;

    /**
     * Construtor padrão que cria uma matriz de 3x3.
     */
    public Matrix() {
        this(3,3);
    }

    /**
     * Construtor que cria uma matriz de tamanho específico.
     *
     * @param row Número de linhas da matriz
     * @param column Número de colunas da matriz
     */
    public Matrix(int row, int column) {
        this.row = row;
        this.column = column;
        this.start = new Cell();

        int line = 0;
        Cell i = this.start;

        while (line < this.row) {
            Cell ancor = i;

            for (int col = 1; col < this.column; i = i.right, col++) {
                Cell temp = new Cell();
                i.right = temp;
                temp.left = i;
            }

            i = ancor;

            if (line > 0 && line <= this.row) {
                int col = 1;

                for (Cell j = i.top; col <= this.column; j = j.right, i = i.right, col++) {
                    j.bottom = i;
                    i.top = j;
                }

                i = ancor;
            }

            if (line < this.row - 1) {
                i.bottom = new Cell();
                i.bottom.top = i;
                i = i.bottom;
            }

            line++;
        }
    }

    /**
     * Soma a matriz atual com outra matriz, retornando uma nova matriz com o resultado.
     *
     * @param m Matriz a ser somada com a matriz atual
     * @return Nova matriz resultante da soma
     * @throws Exception Se as matrizes não tiverem as mesmas dimensões
     */
    public Matrix soma(Matrix m) throws Exception {
        if (this.row != m.row || this.column != m.column) {
            throw new Exception("As matrizes devem ter as mesmas dimensões para serem somadas.");
        }
    
        Matrix response = new Matrix(this.row, this.column);
        
        for (Cell ai = this.start, bi = m.start, ci = response.start; ai != null; ai = ai.bottom, bi = bi.bottom, ci = ci.bottom) {
            for (Cell aj = ai, bj = bi, cj = ci; aj != null; aj = aj.right, bj = bj.right, cj = cj.right) {
                cj.element = aj.element + bj.element;
            }
        }
    
        return response;
    }

    /**
     * Multiplica a matriz atual com outra matriz, retornando uma nova matriz com o resultado.
     *
     * @param m Matriz a ser multiplicada com a matriz atual
     * @return Nova matriz resultante da multiplicação
     * @throws Exception Se as dimensões forem incompatíveis para multiplicação
     */
    public Matrix multiplicacao(Matrix m) throws Exception {
        if (this.column != m.row) {
            throw new Exception("Dimensões incompatíveis para a multiplicação.");
        }
    
        Matrix response = new Matrix(this.row, m.column);
    
        for (Cell ai = this.start, ci = response.start; ai != null; ai = ai.bottom, ci = ci.bottom) { 
            Cell mColStart = m.start;

            for (Cell cj = ci; cj != null; cj = cj.right) { 
                Cell aij = ai; 
                Cell bj = mColStart; 
                int mult = 0;

                while (aij != null && bj != null) { 
                    mult += aij.element * bj.element;
                    aij = aij.right; 
                    bj = bj.bottom;   
                }

                cj.element = mult; 
                mColStart = mColStart.right; 
            }
        }
    
        return response;
    }

    /**
     * Verifica se a matriz é quadrada.
     *
     * @return true se a matriz for quadrada, false caso contrário
     */
    public boolean isSquare() {
        return (this.row == this.column);
    }

    /**
     * Exibe a diagonal principal da matriz.
     */
    public void mostrarDiagonalPrincipal() {
        if (isSquare() == true) {
            Cell i = this.start;

            while (i != null) {
                System.out.print(i.element + " ");
                i = i.right;

                if (i != null) {
                    i = i.bottom;
                }
            }

            System.out.println();
        }
    }

    /**
     * Exibe a diagonal secundária da matriz.
     */
    public void mostrarDiagonalSecundaria() {
        if (isSquare() == true) {
            Cell i = this.start;

            for (; i.right != null; i = i.right);

            while (i != null) {
                System.out.print(i.element + " ");
                i = i.left;

                if (i != null) {
                    i = i.bottom;
                }
            }
            
            System.out.println();
        }
    }

    /**
     * Insere um elemento em uma posição específica da matriz.
     *
     * @param x Valor a ser inserido
     * @param rowPos Linha onde o valor será inserido
     * @param columnPos Coluna onde o valor será inserido
     */
    public void insert(int x, int rowPos, int columnPos) {
        if (rowPos >= this.row || columnPos >= this.column || rowPos < 0 || columnPos < 0) {
            try {
                throw new Exception("Posição inválida.");
            } catch(Exception e) {
                e.printStackTrace();
            }
        } else {
            Cell temp = start;

            for (int i = 0; i < columnPos; i++) {
                temp = temp.right;
            }

            for (int i = 0; i < rowPos; i++) {
                temp = temp.bottom;
            }

            temp.element = x;
        }
    }

    /**
     * Lê elementos da matriz a partir de uma entrada de Scanner.
     *
     * @param sc Scanner usado para a entrada dos elementos
     * @throws Exception Se a célula inicial estiver vazia
     */
    public void insertRead(Scanner sc) throws Exception {
        if (start == null) {
            throw new Exception("Erro ao inserir.");
        }

        for (Cell i = this.start; i != null; i = i.bottom) {
            for (Cell j = i; j != null; j = j.right) {
                j.element = sc.nextInt();
            }
        }
    }

    /**
     * Exibe a matriz completa no console.
     */
    public void show() {
        for (Cell i = this.start; i != null; i = i.bottom) {
            for (Cell j = i; j != null; j = j.right) {
                System.out.print(j.element + " ");
            }

            System.out.println();
        }
    }
}

/**
 * Classe principal para manipulação de matrizes dinâmicas, realizando operações de soma,
 * multiplicação e exibição de diagonais principais e secundárias.
 */
public class DynamicMatrix {
    public static int comparisons;
    public static int movements;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int operationsNumber = 0;

        operationsNumber = sc.nextInt();

        for (int i = 0; i < operationsNumber; i++) {
            int rowsNumber = sc.nextInt();
            int columnsNumber = sc.nextInt();

            Matrix matrix1 = new Matrix(rowsNumber, columnsNumber);

            try {
                matrix1.insertRead(sc);
            } catch(Exception e) {
                System.out.println("Erro ao ler o arquivo.");
            }

            rowsNumber = sc.nextInt();
            columnsNumber = sc.nextInt();

            Matrix matrix2 = new Matrix(rowsNumber, columnsNumber);

            try {
                matrix2.insertRead(sc);
            } catch(Exception e) {
                System.out.println("Erro ao inserir.");
            }

            matrix1.mostrarDiagonalPrincipal();
            matrix1.mostrarDiagonalSecundaria();

            try {
                Matrix additionMatrix = matrix1.soma(matrix2);
                Matrix multiplicationMatrix = matrix1.multiplicacao(matrix2);
                
                additionMatrix.show();
                multiplicationMatrix.show();
            } catch (Exception e) {
                System.out.println("Erro ao mostrar soma ou multiplicação: " + e.getMessage());
            }
        }

        sc.close();
    }
}