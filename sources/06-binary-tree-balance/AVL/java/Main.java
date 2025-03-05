/**
 * Código fonte - Implementação da Árvore Binária de Pesquisa AVL
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type AVL Tree
 * @language Java
 * @version 1.0
 */

class Node {
    public int element;
    public Node left, right;
    public int level;

    public Node(int element) {
        this.element = element;
        this.left = this.right = null;
        this.level = 1;
    }

    public Node(int element, Node left, Node right, int level) {
        this.element = element;
        this.left = left;
        this.right = right;
        this.level = level;
    }

    public void setLevel() {
        this.level = 1 + Math.max(getLevel(left), getLevel(right));
    }

    public static int getLevel(Node node) {
        return (node == null) ? 0 : node.level;
    }
}

class AVL {
    private Node root;

    public AVL() {
        root = null;
    }

    public boolean search(int value) {
        return search(value, root);
    }

    private boolean search(int value, Node node) {
        boolean found;

        if (node == null) {
            found = false;
        } else if (value == node.element) {
            found = true;
        } else if (value < node.element) {
            found = search(value, node.left);
        } else {
            found = search(value, node.right);
        }

        return found;
    }

    public void centralWalk() {
        System.out.print("[ ");
        centralWalk(root);
        System.out.println("]");
    }

    private void centralWalk(Node node) {
        if (node != null) {
            centralWalk(node.left);
            System.out.print(node.element + " ");
            centralWalk(node.right);
        }
    }

    public void preOrderWalk() {
        System.out.print("[ ");
        preOrderWalk(root);
        System.out.println("]");
    }

    private void preOrderWalk(Node node) {
        if (node != null) {
            System.out.print(node.element + " ");
            preOrderWalk(node.left);
            preOrderWalk(node.right);
        }
    }

    public void postOrderWalk() {
        System.out.print("[ ");
        postOrderWalk(root);
        System.out.println("]");
    }

    private void postOrderWalk(Node node) {
        if (node != null) {
            postOrderWalk(node.left);
            postOrderWalk(node.right);
            System.out.print(node.element + " ");
        }
    }

    public void insert(int value) {
        root = insert(value, root);
    }

    private Node insert(int value, Node node) {
        if (node == null) {
            node = new Node(value);
        } else if (value < node.element) {
            node.left = insert(value, node.left);
        } else if (value > node.element) {
            node.right = insert(value, node.right);
        } else {
            System.out.println("Erro ao inserir nó na árvore binária.");
        }

        return balance(node);
    }

    public void remove(int value) {
        root = remove(value, root);
    }

    private Node remove(int value, Node node) {
        if (node == null) {
            System.out.println("Erro ao remover nó da árvore binária.");
        } else if (value < node.element) {
            node.left = remove(value, node.left);
        } else if (value > node.element) {
            node.right = remove(value, node.right);
        } else if (node.right == null) {
            node = node.left;
        } else if (node.left == null) {
            node = node.right;
        } else {
            node.left = largerLeft(node, node.left);
        }

        return balance(node);
    }

    private Node largerLeft(Node i, Node j) {
        if (j.right == null) {
            i.element = j.element;
            j = j.left;
        } else {
            j.right = largerLeft(i, j.right);
        }

        return j;
    }

    private Node balance(Node node) {
        if (node != null) {
            int factor = Node.getLevel(node.right) - Node.getLevel(node.left);

            if (Math.abs(factor) <= 1) {
                node.setLevel();
            } else if (factor == 2) {
                int rightSonFactor = Node.getLevel(node.right.right) - Node.getLevel(node.right.left);

                if (rightSonFactor == -1) {
                    node.right = rightRotate(node.right);
                }

                node = leftRotate(node);
            } else if (factor == -2) {
                int leftSonFactor = Node.getLevel(node.left.right) - Node.getLevel(node.left.left);

                if (leftSonFactor == 1) {
                    node.left = leftRotate(node.left);
                }

                node = rightRotate(node);
            } else {
                System.out.println("Erro ao balancear [arvore binária.");
            }
        }

        return node;
    }

    private Node rightRotate(Node node) {
        Node leftNode = node.left;
        Node leftRightNode = leftNode.right;

        leftNode.right = node;
        node.left = leftRightNode;

        node.setLevel();
        leftNode.setLevel();

        return leftNode;
    }

    private Node leftRotate(Node node) {
        Node rightNode = node.right;
        Node rightLeftNode = rightNode.left;

        rightNode.left = node;
        node.right = rightLeftNode;

        node.setLevel();
        rightNode.setLevel();

        return rightNode;
    }
}

public class Main {
    public static void main(String[] args) {
        try {
            AVL avl = new AVL();
            int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

            for (int item : array) {
                System.out.println("Inserindo -> " + item);
                avl.insert(item);
                avl.preOrderWalk();
            }
        } catch (Exception erro) {
            System.out.println(erro.getMessage());
        }
    }
}