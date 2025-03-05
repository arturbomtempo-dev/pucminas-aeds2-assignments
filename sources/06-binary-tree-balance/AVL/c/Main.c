#include <stdio.h>
#include <stdlib.h>

/**
 * Código fonte - Implementação da Árvore Binária de Pesquisa AVL
 *
 * @author Artur Bomtempo Colen
 * @algorithm Data Structure
 * @type AVL Tree
 * @language C
 * @version 1.0
 */

typedef struct NodeAVL {
    int element;
    struct NodeAVL *left;
    struct NodeAVL *right;
    int level;
} NodeAVL;

typedef struct AVL {
    NodeAVL *root;
} AVL;

NodeAVL *createNode(int element) {
    NodeAVL *newNode = (NodeAVL *)malloc(sizeof(NodeAVL));

    newNode->element = element;
    newNode->left = newNode->right = NULL;
    newNode->level = 1;

    return newNode;
}

void setLevel(NodeAVL *node) {
    node->level = 1 + (node->left ? node->left->level : 0) >
                          (node->right ? node->right->level : 0)
                      ? (node->left ? node->left->level : 0)
                      : (node->right ? node->right->level : 0);
}

int getLevel(NodeAVL *node) { return node ? node->level : 0; }

NodeAVL *rightRotate(NodeAVL *node) {
    NodeAVL *leftNode = node->left;
    NodeAVL *leftRightNode = leftNode->right;

    leftNode->right = node;
    node->left = leftRightNode;

    setLevel(node);
    setLevel(leftNode);

    return leftNode;
}

NodeAVL *leftRotate(NodeAVL *node) {
    NodeAVL *rightNode = node->right;
    NodeAVL *rightLeftNode = rightNode->left;

    rightNode->left = node;
    node->right = rightLeftNode;

    setLevel(node);
    setLevel(rightNode);

    return rightNode;
}

NodeAVL *balance(NodeAVL *node) {
    if (node) {
        int factor = getLevel(node->right) - getLevel(node->left);

        if (abs(factor) <= 1) {
            setLevel(node);
        } else if (factor == 2) {
            if (getLevel(node->right->left) > getLevel(node->right->right)) {
                node->right = rightRotate(node->right);
            }
            node = leftRotate(node);
        } else if (factor == -2) {
            if (getLevel(node->left->right) > getLevel(node->left->left)) {
                node->left = leftRotate(node->left);
            }

            node = rightRotate(node);
        }
    }
    
    return node;
}

NodeAVL *insert(int value, NodeAVL *node) {
    if (node == NULL) {
        return createNode(value);
    } else if (value < node->element) {
        node->left = insert(value, node->left);
    } else if (value > node->element) {
        node->right = insert(value, node->right);
    }

    return balance(node);
}

void preOrderWalk(NodeAVL *node) {
    if (node != NULL) {
        printf("%d ", node->element);
        preOrderWalk(node->left);
        preOrderWalk(node->right);
    }
}

void preOrder(AVL *tree) {
    printf("[ ");
    preOrderWalk(tree->root);
    printf("]\n");
}

AVL *createAVL() {
    AVL *tree = (AVL *)malloc(sizeof(AVL));
    tree->root = NULL;
    return tree;
}

int main() {
    AVL *tree = createAVL();
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < length; i++) {
        int value = array[i];
        printf("Inserindo -> %d\n", value);
        tree->root = insert(value, tree->root);
        preOrder(tree);
    }

    free(tree);

    return 0;
}