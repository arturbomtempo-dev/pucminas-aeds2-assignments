/**
 * Código fonte - Implementação da Árvore Binária de Pesquisa Red-Black
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type Red-Black Tree
 * @language Java
 * @version 1.0
 */

class NodeAN {
    public boolean color;
    public int element;
    public NodeAN left, right;

    public NodeAN() {
        this.color = false;
        this.element = 0;
        this.left = this.right = null;
    }

    public NodeAN(int element) {
        this.color = false;
        this.element = element;
        this.left = this.right = null;
    }

    public NodeAN(int element, boolean color) {
        this.color = color;
        this.element = element;
        this.left = this.right = null;
    }

    public NodeAN(int element, boolean color, NodeAN left, NodeAN right) {
        this.color = color;
        this.element = element;
        this.left = left;
        this.right = right;
    }
}

class RedBlack {
    private NodeAN root;

    public RedBlack() {
        root = null;
    }

    public boolean search(int value) {
        return search(value, root);
    }

    private boolean search(int value, NodeAN node) {
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

    private void centralWalk(NodeAN node) {
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

    private void preOrderWalk(NodeAN node) {
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

    private void postOrderWalk(NodeAN node) {
        if (node != null) {
            postOrderWalk(node.left);
            postOrderWalk(node.right);
            System.out.print(node.element + " ");
        }
    }

    public void insert(int value) {
        if (root == null) {
            root = new NodeAN(value);
        } else if (root.left == null && root.right == null) {
            if (value < root.element) {
                root.left = new NodeAN(value);
            } else {
                root.right = new NodeAN(value);
            }
        } else if (root.left == null) {
            if (value < root.element) {
                root.left = new NodeAN(value);
            } else if (value < root.right.element) {
                root.left = new NodeAN(root.element);
                root.element = value;
            } else {
                root.left = new NodeAN(root.element);
                root.element = root.right.element;
                root.right.element = value;
            }
        } else if (root.right == null) {
            if (value > root.element) {
                root.right = new NodeAN(value);
            } else if (value > root.left.element) {
                root.right = new NodeAN(root.element);
                root.element = value;
            } else {
                root.right = new NodeAN(root.element);
                root.element = root.left.element;
                root.left.element = value;
            }

            root.left.color = root.right.color = false;
        } else {
            insert(value, null, null, null, root);
        }
    }

    private void balance(NodeAN greatGrandfather, NodeAN grandfather, NodeAN father, NodeAN i) {
        if (father.color == true) {
            if (father.element > grandfather.element) {
                if (i.element > father.element) {
                    grandfather = leftRotate(grandfather);
                } else {
                    grandfather = rightLeftRotate(grandfather);
                }
            } else {
                if (i.element < father.element) {
                    grandfather = rightRotate(grandfather);
                } else {
                    grandfather = leftRightRotate(grandfather);
                }
            }

            if (greatGrandfather == null) {
                root = grandfather;
            } else if (grandfather.element < greatGrandfather.element) {
                greatGrandfather.left = grandfather;
            } else {
                greatGrandfather.right = grandfather;
            }

            grandfather.color = false;
            grandfather.left.color = grandfather.right.color = true;
        }
    }

    private void insert(int value, NodeAN greatGrandfather, NodeAN grandfather, NodeAN father, NodeAN i) {
        if (i == null) {
            if (value < father.element) {
                i = father.left = new NodeAN(value, true);
            } else {
                i = father.right = new NodeAN(value, true);
            }

            if (father.color == true) {
                balance(greatGrandfather, grandfather, father, i);
            }
        } else {
            if (i.left != null && i.right != null && i.left.color == true && i.right.color == true) {
                i.color = true;
                i.left.color = i.right.color = false;

                if (i == root) {
                    i.color = false;
                } else if (father.color == true) {
                    balance(greatGrandfather, grandfather, father, i);
                }
            }

            if (value < i.element) {
                insert(value, grandfather, father, i, i.left);
            } else if (value > i.element) {
                insert(value, grandfather, father, i, i.right);
            } else {
                System.out.println("Erro ao insert nó na árvore binária.");
            }
        }
    }

    private NodeAN rightRotate(NodeAN node) {
        NodeAN leftNode = node.left;
        NodeAN leftRightNode = leftNode.right;

        leftNode.right = node;
        node.left = leftRightNode;

        return leftNode;
    }

    private NodeAN leftRotate(NodeAN node) {
        NodeAN rightNode = node.right;
        NodeAN rightLeftNode = rightNode.left;

        rightNode.left = node;
        node.right = rightLeftNode;

        return rightNode;
    }

    private NodeAN rightLeftRotate(NodeAN node) {
        node.right = rightRotate(node.right);
        return leftRotate(node);
    }

    private NodeAN leftRightRotate(NodeAN node) {
        node.left = leftRotate(node.left);
        return rightRotate(node);
    }
}

public class Main {
    public static void main(String[] args) {
        RedBlack tree = new RedBlack();

        tree.insert(4);
        tree.preOrderWalk();
        tree.insert(35);
        tree.preOrderWalk();
        tree.insert(10);
        tree.preOrderWalk();
        tree.insert(13);
        tree.preOrderWalk();
        tree.insert(3);
        tree.preOrderWalk();
        tree.insert(30);
        tree.preOrderWalk();
        tree.insert(15);
        tree.preOrderWalk();
        tree.insert(12);
        tree.preOrderWalk();
        tree.insert(7);
        tree.preOrderWalk();
        tree.insert(40);
        tree.preOrderWalk();
        tree.insert(20);
        tree.preOrderWalk();
    }
}