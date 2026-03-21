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

AVLNode* CreateAVLNode(const char value[])
{
    size_t len = strlen(value);
    AVLNode* node = malloc(sizeof(AVLNode) + len + 1);

    if (node == NULL) {
        return NULL;
    }

    strcpy(node->value, value);
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

static AVLNode* insert(AVLNode* node, const char value[]) {
    if (node == NULL) {
        return CreateAVLNode(value);
    }

    if (strcmp(node->value, value) < 0) {
        node->left = insert(node->left, value);
    } else if (strcmp(node->value, value) > 0) {
        node->right = insert(node->right, value);
    } else {
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

void AVLTreeInsert(AVLTree* tree, const char value[])
{
    if (tree == NULL) {
        return;
    }

    tree->root = insert(tree->root, value);
}

static AVLNode* deleteNode(AVLNode* node, const char value[]) {
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(value, node->value) < 0) {
        node->left = deleteNode(node->left, value);
    } else if (strcmp(value, node->value) > 0) {
        node->right = deleteNode(node->right, value);
    } else {
        if (node->left == NULL) {
            AVLNode* rightChild = node->right;
            free(node);
            return rightChild;
        } else if (node->right == NULL) {
            AVLNode* leftChild = node->left;
            free(node);
            return leftChild;
        }

        AVLNode* successor = node->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }

        AVLNode* newNode = CreateAVLNode(successor->value);
        if (newNode == NULL) {
            return node;
        }

        newNode->left = node->left;
        newNode->right = node->right;
        newNode->height = node->height;

        free(node);

        newNode->right = deleteNode(newNode->right, successor->value);

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

AVLNode* AVLTreeFind(AVLTree* tree, const char value[]) {
    AVLNode* current = tree->root;

    while (current != NULL) {
        if (strcmp(value, current->value) == 0) {
            return current;
        } else if (strcmp(value, current->value) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

void AVLTreeDelete(AVLTree* tree, const char value[]) {
    if (tree == NULL) {
        return;
    }

    tree->root = deleteNode(tree->root, value);
}

void NodeFree(AVLNode* node)
{
    if (node == NULL) {
        return;
    }

    if (node->left != NULL) {
        NodeFree(node->left);
        node->left = NULL;
    }

    if (node->right != NULL) {
        NodeFree(node->right);
        node->right = NULL;
    }

    free(node);
}

void FreeAVLTree(AVLTree* tree) {
    if (tree == NULL) {
        return;
    }

    NodeFree(tree->root);

    free(tree);
}