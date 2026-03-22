#include "AVL-Tree.h"
#include <stdlib.h>
#include <string.h>

AVLTree* CreateAVLTree()
{
    AVLTree* tree = malloc(sizeof(AVLTree));

    if (tree == NULL) {
        return NULL;
    }

    tree->root = NULL;

    return tree;
}

AVLNode* CreateAVLNode(const char code[], const char name[])
{
    AVLNode* node = malloc(sizeof(AVLNode));

    if (node == NULL) {
        return NULL;
    }

    node->code = malloc(strlen(code) + 1);
    node->name = malloc(strlen(name) + 1);

    if (node->code == NULL || node->name == NULL) {
        free(node->code);
        free(node->name);
        free(node);
        return NULL;
    }

    strcpy(node->code, code);
    strcpy(node->name, name);
    node->left = NULL;
    node->right = NULL;
    node->height = 0;

    return node;
}

static int getHeight(AVLNode* node)
{
    if (node == NULL) {
        return -1;
    }

    return node->height;
}

static void updateHeight(AVLNode* node)
{
    if (node == NULL) {
        return;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    if (leftHeight > rightHeight) {
        node->height = leftHeight + 1;
    } else {
        node->height = rightHeight + 1;
    }
}

static AVLNode* leftRotate(AVLNode* node)
{
    AVLNode* right_node = node->right;
    AVLNode* left_node = right_node->left;

    right_node->left = node;
    node->right = left_node;

    updateHeight(node);
    updateHeight(right_node);

    return right_node;
}

static AVLNode* rightRotate(AVLNode* node)
{
    AVLNode* left_node = node->left;
    AVLNode* right_node = left_node->right;

    left_node->right = node;
    node->left = right_node;

    updateHeight(node);
    updateHeight(left_node);

    return left_node;
}

static AVLNode* insert(AVLNode* node, const char code[], const char name[]) {
    if (node == NULL) {
        return CreateAVLNode(code, name);
    }

    if (strcmp(code, node->code) < 0) {
        node->left = insert(node->left, code, name);
    } else if (strcmp(code, node->code) > 0) {
        node->right = insert(node->right, code, name);
    } else {
        free(node->name);
        node->name = malloc(strlen(name) + 1);
        if (node->name) {
            strcpy(node->name, name);
        }
        return node;
    }

    updateHeight(node);

    int balance = getHeight(node->right) - getHeight(node->left);

    if (balance < -1) {
        int leftBalance = getHeight(node->left->right) - getHeight(node->left->left);
        if (leftBalance > 0) {
            node->left = leftRotate(node->left);
        }
        return rightRotate(node);
    }

    if (balance > 1) {
        int rightBalance = getHeight(node->right->right) - getHeight(node->right->left);
        if (rightBalance < 0) {
            node->right = rightRotate(node->right);
        }
        return leftRotate(node);
    }

    return node;
}

int AVLTreeInsert(AVLTree* tree, const char code[], const char name[])
{
    if (tree == NULL) {
        return 0;
    }

    tree->root = insert(tree->root, code, name);
    return 1;
}

AVLNode* AVLTreeFind(AVLTree* tree, const char code[])
{
    AVLNode* current = tree->root;

    while (current != NULL) {
        if (strcmp(code, current->code) == 0) {
            return current;
        } else if (strcmp(code, current->code) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

static AVLNode* deleteNode(AVLNode* node, const char code[])
{
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(code, node->code) < 0) {
        node->left = deleteNode(node->left, code);
    } else if (strcmp(code, node->code) > 0) {
        node->right = deleteNode(node->right, code);
    } else {
        if (node->left == NULL) {
            AVLNode* rightChild = node->right;
            free(node->code);
            free(node->name);
            free(node);
            return rightChild;
        } else if (node->right == NULL) {
            AVLNode* leftChild = node->left;
            free(node->code);
            free(node->name);
            free(node);
            return leftChild;
        }

        AVLNode* successor = node->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }

        AVLNode* newNode = CreateAVLNode(successor->code, successor->name);
        if (newNode == NULL) {
            return node;
        }

        newNode->left = node->left;
        newNode->right = node->right;
        newNode->height = node->height;

        free(node->code);
        free(node->name);
        free(node);

        newNode->right = deleteNode(newNode->right, successor->code);

        node = newNode;
    }

    updateHeight(node);

    int balance = getHeight(node->right) - getHeight(node->left);

    if (balance < -1) {
        int leftBalance = getHeight(node->left->right) - getHeight(node->left->left);
        if (leftBalance > 0) {
            node->left = leftRotate(node->left);
        }
        return rightRotate(node);
    }

    if (balance > 1) {
        int rightBalance = getHeight(node->right->right) - getHeight(node->right->left);
        if (rightBalance < 0) {
            node->right = rightRotate(node->right);
        }
        return leftRotate(node);
    }

    return node;
}

int AVLTreeDelete(AVLTree* tree, const char code[])
{
    if (tree == NULL) {
        return 0;
    }

    tree->root = deleteNode(tree->root, code);
    return 1;
}

void NodeFree(AVLNode* node)
{
    if (node == NULL) {
        return;
    }

    NodeFree(node->left);
    NodeFree(node->right);
    free(node->code);
    free(node->name);

    free(node);
}

void FreeAVLTree(AVLTree* tree)
{
    if (tree == NULL) {
        return;
    }

    NodeFree(tree->root);

    free(tree);
}