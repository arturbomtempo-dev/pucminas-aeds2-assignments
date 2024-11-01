class Queue {
    private int[] array;
    private int first;
    private int last;

    public Queue() {
        this.array = new int[6];
        this.first = this.last = 0;
    }

    public Queue(int length) {
        this.array = new int[length];
        this.first = this.last = 0;
    }

    public void insert(int value) {
        if (((last + 1) % array.length) == first) {
            throw new Error("Erro ao inserir dado na fila.");
        }

        array[last] = value;
        last = (last + 1) % array.length;
    }

    public int remove() {
        if (first == last) {
            throw new Error("Erro ao remover dado da fila.");
        }

        int valueRemoved = array[first];
        first = (first + 1) % array.length;
        return valueRemoved;
    }

    public void show() {
        System.out.print("[");

        for(int i = first; i != last; i = ((i + 1) % array.length)) {
            System.out.print(array[i] + ", ");
        }
   
        System.out.println("]");
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("===== Fila Circular =====");

        Queue queue = new Queue(6);
        int x1, x2, x3;

        queue.insert(1);
        queue.insert(7);
        queue.insert(9);
        queue.insert(8);
        queue.insert(4);

        queue.show();

        x1 = queue.remove();
        x2 = queue.remove();
        x3 = queue.remove();

        System.out.println("Removidos: " + x1 + ", " + x2 + ", " + x3);

        queue.show();

        queue.insert(5);
        queue.insert(6);

        queue.show();
    }
}