#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Node {
    int element;
    struct Node *left, *right;
    int level;
} typedef Node;

Node *root;

void start() {
    root = NULL;
}

Node* createNode(int element) {
    Node *new = (Node *) malloc(sizeof(Node));
    new->element = element;
    new->left = new->right = NULL;
    new->level = 1;
    return new;
}

int getLevel(Node *node) {
    return (node == NULL) ? 0 : node->level;
}

void setLevel(Node *node) {
    if (node != NULL) {
        node->level = 1 + fmax(getLevel(node->left), getLevel(node->right));
    }
}

Node* rightRotate(Node *node) {
    Node *leftNode = node->left;
    Node *leftRightNode = leftNode->right;

    leftNode->right = node;
    node->left = leftRightNode;

    setLevel(node);
    setLevel(leftNode);

    return leftNode;
}

Node* leftRotate(Node *node) {
    Node *rightNode = node->right;
    Node *rightLeftNode = rightNode->left;

    rightNode->left = node;
    node->right = rightLeftNode;

    setLevel(node);
    setLevel(rightNode);

    return rightNode;
}

Node* balance(Node *node) {
    if (node != NULL) {
        int factor = getLevel(node->right) - getLevel(node->left);

        if (factor == 2) {
            int rightSonFactor =  getLevel(node->right->right) - getLevel(node->right->left);

            if (rightSonFactor == -1) {
                node->right = rightRotate(node->right);
            }

            node = leftRotate(node);
        } else if (factor == -2) {
            int leftSonFactor =  getLevel(node->left->right) - getLevel(node->left->left);

            if (leftSonFactor == 1) {
                node->left = leftRotate(node->left);
            }

            node = rightRotate(node);
        } else {
            setLevel(node);
        }
    }

    return node;
}

Node* insert(Node *node, int element) {
    if (node == NULL) {
        node = createNode(element);
    } else if (element < node->element) {
        node->left = insert(node->left, element);
    } else if (element > node->element) {
        node->right = insert(node->right, element);
    }

    node = balance(node);

    return node;
}

void recursivePreOrderWalk(Node *node) {
    if (node != NULL) {
        printf("%d ", node->element);
        recursivePreOrderWalk(node->left);
        recursivePreOrderWalk(node->right);
    }
}

void preOrderWalk() {
    printf("[ ");
    recursivePreOrderWalk(root);
    printf(" ]");
}

int main() {
    start();

    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int length = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < length; i++) {
        printf("Inserindo -> %d\n", array[i]);
        root = insert(root, array[i]);
        preOrderWalk();
        printf("\n");
    }

    return 0;
}