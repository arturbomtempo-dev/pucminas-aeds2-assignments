#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct NodeAN {
    bool color;
    int element;
    struct NodeAN *left;
    struct NodeAN *right;
} typedef NodeAN;

struct Alvinegra {
    NodeAN *root;
} typedef Alvinegra;

NodeAN* createNode(int element) {
    NodeAN *newNode = (NodeAN *) malloc(sizeof(NodeAN));
    newNode->color = false;  
    newNode->element = element;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void preOrderWalk(NodeAN *node) {
    if (node != NULL) {
        printf("%d ", node->element);
        preOrderWalk(node->left);
        preOrderWalk(node->right);
    }
}

void recursivepreOrderWalk(Alvinegra *tree) {
    printf("[ ");
    preOrderWalk(tree->root);
    printf("]\n");
}

NodeAN* rightRotate(NodeAN *node) {
    NodeAN *leftNode = node->left;
    NodeAN *leftRightNode = leftNode->right;

    leftNode->right = node;
    node->left = leftRightNode;

    return leftNode;
}

NodeAN* leftRotate(NodeAN *node) {
    NodeAN *rightNode = node->right;
    NodeAN *rightLeftNode = rightNode->left;

    rightNode->left = node;
    node->right = rightLeftNode;

    return rightNode;
}

NodeAN* rightLeftRotate(NodeAN *node) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

NodeAN* leftRightRotate(NodeAN *node) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

void balance(NodeAN *greatGrandfather, NodeAN *grandfather, NodeAN *father, NodeAN *i, Alvinegra *tree) {
    if (father->color == true) {
        if (father->element > grandfather->element) {
            if (i->element > father->element) {
                grandfather = leftRotate(grandfather);
            } else {
                grandfather = rightLeftRotate(grandfather);
            }
        } else {
            if (i->element < father->element) {
                grandfather = rightRotate(grandfather);
            } else {
                grandfather = leftRightRotate(grandfather);
            }
        }

        if (greatGrandfather == NULL) {
            tree->root = grandfather;
        } else if (grandfather->element < greatGrandfather->element) {
            greatGrandfather->left = grandfather;
        } else {
            greatGrandfather->right = grandfather;
        }

        grandfather->color = false;
        grandfather->left->color = grandfather->right->color = true;
    }
}

void insert(int value, NodeAN *greatGrandfather, NodeAN *grandfather, NodeAN *father, NodeAN *i, Alvinegra *tree) {
    if (i == NULL) {
        if (value < father->element) {
            i = father->left = createNode(value);
            i->color = true;
        } else {
            i = father->right = createNode(value);
            i->color = true;
        }

        if (father->color == true) {
            balance(greatGrandfather, grandfather, father, i, tree);
        }
    } else {
        if (i->left != NULL && i->right != NULL && i->left->color == true && i->right->color == true) {
            i->color = true;
            i->left->color = i->right->color = false;
            if (i == tree->root) {
                i->color = false;
            } else if (father->color == true) {
                balance(greatGrandfather, grandfather, father, i, tree);
            }
        }

        if (value < i->element) {
            insert(value, grandfather, father, i, i->left, tree);
        } else if (value > i->element) {
            insert(value, grandfather, father, i, i->right, tree);
        } else {
            printf("Erro ao inserir nó na árvore binária.\n");
        }
    }
}

void alvinegraInsert(Alvinegra *tree, int value) {
    if (tree->root == NULL) {
        tree->root = createNode(value);
    } else {
        insert(value, NULL, NULL, NULL, tree->root, tree);
    }
}

Alvinegra* createAlvinegra() {
    Alvinegra* tree = (Alvinegra*)malloc(sizeof(Alvinegra));
    tree->root = NULL;
    return tree;
}

int main() {
    Alvinegra *tree = createAlvinegra();

    alvinegraInsert(tree, 4);
    recursivepreOrderWalk(tree);
    alvinegraInsert(tree, 35);
    recursivepreOrderWalk(tree);
    alvinegraInsert(tree, 10);
    recursivepreOrderWalk(tree);
    alvinegraInsert(tree, 13);
    recursivepreOrderWalk(tree);
    alvinegraInsert(tree, 3);
    recursivepreOrderWalk(tree);
    alvinegraInsert(tree, 30);
    recursivepreOrderWalk(tree);
    alvinegraInsert(tree, 15);
    recursivepreOrderWalk(tree);
    alvinegraInsert(tree, 12);
    recursivepreOrderWalk(tree);
    alvinegraInsert(tree, 7);
    recursivepreOrderWalk(tree);
    alvinegraInsert(tree, 40);
    recursivepreOrderWalk(tree);
    alvinegraInsert(tree, 20);
    recursivepreOrderWalk(tree);

    free(tree);

    return 0;
}