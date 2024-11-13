#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

struct Node {
    int element;
    struct Node *left, *right;
} typedef Node;

Node *root;

Node* newNode(int element) {
    Node *new = (Node *) malloc (sizeof(Node));
    new->element = element;
    new->left = new->right = NULL;
    return new;
}

void start() {
    root = NULL;
}

Node* recursiveInsert(int value, Node *i) {
    if (i == NULL) {
        i = newNode(value);
    } else if (value < i->element) {
        i->left = recursiveInsert(value, i->left);
    } else if (value > i->element) {
        i->right = recursiveInsert(value, i->right);
    } else {
        errx(1, "Erro ao inserir elemento na árvore binária");
    }

    return i;
}

void insert(int value) {
    root = recursiveInsert(value, root);
}

bool recursiveSearch(int value, Node *i) {
    bool found;

    if (i == NULL) {
        found = false;
    } else if (value == i->element) {
        found = true;
    } else if (value < i->element) {
        found = recursiveSearch(value, i->left);
    } else if (value > i->element) {
        found = recursiveSearch(value, i->right);
    }

    return found;
}

bool search(int value) {
    return recursiveSearch(value, root);
}

void recursiveCentralWalk(Node *i) {
    if (i != NULL) {
        recursiveCentralWalk(i->left);
        printf("%d ", i->element);
        recursiveCentralWalk(i->right);
    }
}

void centralWalk() {
    printf("[ ");
    recursiveCentralWalk(root);
    printf("]\n");
}

void recursivePreOrderWalk(Node *i) {
    if (i != NULL) {
        printf("%d ", i->element);
        recursivePreOrderWalk(i->left);
        recursivePreOrderWalk(i->right);
    }
}

void preOrderWalk() {
    printf("[ ");
    recursivePreOrderWalk(root);
    printf("]\n");
}

void recursivePostOrderWalk(Node *i) {
    if (i != NULL) {
        recursivePostOrderWalk(i->left);
        recursivePostOrderWalk(i->right);
        printf("%d ", i->element);
    }
}

void postOrderWalk() {
    printf("[ ");
    recursivePostOrderWalk(root);
    printf("]\n");
}

void biggerLeft(Node **i, Node **j) {
    if ((*j)->right != NULL) {
        biggerLeft(i, &((*j)->right));
    } else {
        Node *deleted = *j;
        (*i)->element = (*j)->element;
        (*j) = (*j)->left;
        free(deleted);
    }
}

void recursiveRemoval(int value, Node **i) {
    if (*i == NULL) {
        errx(1, "Erro ao remover elemento da árvore binária.");
    } else if (value < (*i)->element) {
        recursiveRemoval(value, &((*i)->left));
    } else if (value > (*i)->element) {
        recursiveRemoval(value, &((*i)->right));
    } else if ((*i)->right == NULL) {
        Node* deleted = *i;
        *i = (*i)->left;
        free(deleted);
    } else if ((*i)->left == NULL) {
        Node* deleted = *i;
        *i = (*i)->right;
        free(deleted);
    } else {
        biggerLeft(i, &((*i)->left));
    }
}

void removal(int value) {
    recursiveRemoval(value, &root);
}

int main() {
    start();

    insert(3);
    insert(5);
    insert(1);
    insert(8);
    insert(2);
    insert(4);
    insert(7);
    insert(6);

    printf("\nInserir: 3, 5, 1, 8, 2, 4, 7 e 6");
    printf("\nCaminhar: central, pre e pos\n");
    centralWalk();
    preOrderWalk();
    postOrderWalk();

    printf("\nRemover: 2");
    printf("\nCaminhar: central, pre e pos\n");
    removal(2);

    centralWalk();
    preOrderWalk();
    postOrderWalk();

    printf("\nVoltando com a árvore inicial");
    printf("\nRemover: 1");
    printf("\nCaminhar: central, pre e pos\n");
    insert(2);
    removal(1);

    centralWalk();
    preOrderWalk();
    postOrderWalk();

    printf("\nVoltando com a árvore inicial");
    printf("\nRemover: 3");
    printf("\nCaminhar: central, pre e pos\n");
    removal(2);
    insert(1);
    insert(2);
    removal(3);

    centralWalk();
    preOrderWalk();
    postOrderWalk();

    return 0;
}