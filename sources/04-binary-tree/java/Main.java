class Node {
    public int element;
    public Node left, right;

    public Node() {
        this.element = 0;
        this.left = this.right = null;
    }

    public Node(int value) {
        this.element = value;
        this.left = this.right = null;
    }

    public Node(int value, Node left, Node right) {
        this.element = value;
        this.left = left;
        this.right = right;
    }
}

class BinaryTree {
    private Node root;

    public BinaryTree() {
        this.root = null;
    }

    public void insert(int value) {
        root = insert(value, root);
    }

    private Node insert(int value, Node i) {
        if (i == null) {
            i = new Node(value);
        } else if (value < i.element) {
            i.left = insert(value, i.left);
        } else if (value > i.element) {
            i.right = insert(value, i.right);
        } else {
            throw new Error("Erro ao inserir elemento na árvore binária.");
        }

        return i;
    }

    public void insertFather(int value) {
        if (root == null) {
            root = new Node(value);
        } else if (value < root.element) {
            insertFather(value, root.left, root);
        } else if (value > root.element) {
            insertFather(value, root.right, root);
        } else {
            throw new Error("Erro ao inserir pai.");
        }
    }

    private void insertFather(int value, Node i, Node father) {
	    if (i == null) {
            if (value < father.element) {
                father.left = new Node(value);
            } else {
                father.right = new Node(value);
            }
        } else if (value < i.element) {
            insertFather(value, i.left, i);
        } else if (value > i.element) {
            insertFather(value, i.right, i);
        } else {
            throw new Error("Erro ao inserir pai.");
        }
	}

    public boolean search(int value) {
        return search(value, root);
    }

    private boolean search(int value, Node i) {
        boolean found;

        if (i == null) {
            found = false;
        } else if (value == i.element) {
            found = true;
        } else if (value < i.element) {
            found = search(value, i.left);
        } else {
            found = search(value, i.right);
        }

        return found;
    }

    public void remove(int value) {
        root = remove(value, root);
    }

    private Node remove(int value, Node i) {
        if (i == null) {
            throw new Error("Erro ao remover valor da árvore binária.");
        } else if (value < i.element) {
            i.left = remove(value, i.left);
        } else if (value > i.element) {
            i.right = remove(value, i.right);
        } else if (i.right == null) {
            i = i.left;
        } else if (i.left == null) {
            i = i.right;
        } else {
            i.left = biggerLeft(i, i.left);
        }

        return i;
    }

    private Node biggerLeft(Node i, Node j) {
        if (j.right == null) {
            i.element = j.element;
            j = j.left;
        } else {
            j.right = biggerLeft(i, j.right);
        }

        return j;
    }

    public void centralWalk(Node i) {
        if (i != null) {
            centralWalk(i.left);
            System.out.print(i.element + " ");
            centralWalk(i.right);
        }
    }

    public void preOrderWalk(Node i) {
        if (i != null) {
            System.out.print(i.element + " ");
            preOrderWalk(i.left);
            preOrderWalk(i.right);
        }
    }

    public void postOrderWalk(Node i) {
        if (i != null) {
            postOrderWalk(i.left);
            postOrderWalk(i.right);
            System.out.print(i.element + " ");
        }
    }

    public int getBigger() {
        int bigger = -1;

        if (root != null) {
            Node i;
            for (i = root; i.right != null; i = i.right);
            bigger = i.element;
        }

        return bigger;
    }

    public int getSmaller() {
        int smaller = -1;

        if  (root != null) {
            Node i;
            for (i = root; i.left != null; i = i.left);
            smaller = i.element;
        }

        return smaller;
    }

    public int getHeight() {
        return getHeight(root, 0);
    }

    public int getHeight(Node i, int height){
        if (i == null){
            height--;
        } else {
            int leftHeight = getHeight(i.left, height + 1);
            int rightHeight = getHeight(i.right, height + 1);
            height = (leftHeight > rightHeight) ? leftHeight : rightHeight;
        }

        return height;
    }

    public void printTree() {
        System.out.print("Caminhamento Central: ");
        centralWalk(root);
        System.out.println();
        System.out.print("Caminhamento Pré-Ordem: ");
        preOrderWalk(root);
        System.out.println();
        System.out.print("Caminhamento Pós-Ordem: ");
        postOrderWalk(root);
        System.out.println();
    }
}

public class Main {
    public static void main(String[] args) {
        int[] values = { 50, 30, 70, 20, 40, 60, 80 };
        BinaryTree tree = new BinaryTree();

        System.out.println("Inserindo elementos na árvore:");
        for (int value : values) {
            tree.insert(value);
            System.out.println("Inserido: " + value);
        }

        System.out.println("\nCaminhamentos:");
        tree.printTree();

        System.out.println("\nAltura da árvore: " + tree.getHeight());

        System.out.println("Maior valor: " + tree.getBigger());
        System.out.println("Menor valor: " + tree.getSmaller());

        int searchValue = 40;
        System.out.println("Busca por " + searchValue + ": " + (tree.search(searchValue) ? "Encontrado" : "Não encontrado"));

        int removeValue = 30;

        System.out.println("\nRemovendo o valor " + removeValue + " da árvore.");
        tree.remove(removeValue);

        System.out.println("Árvore após a remoção:");
        tree.printTree();
    }
}