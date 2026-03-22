#pragma once

typedef struct AVLNode {
    char* code;
    char* name;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef struct AVLTree {
    AVLNode* root;
} AVLTree;

// Creating an AVL tree. The tree root is NULL.
AVLTree* CreateAVLTree();

/*
 * Creates an AVL tree node. Inserts the value passed to the function into the node.
 * The initial height of the node is 0.
 */
AVLNode* CreateAVLNode(const char code[], const char name[]);

/*
 * Inserts a value into an AVL tree. After insertion,
 * it checks the balance and rebalances it if necessary.
 */
void AVLTreeInsert(AVLTree* tree, const char code[], const char name[]);

// Finds an element in an AVL tree.
AVLNode* AVLTreeFind(AVLTree* tree, const char code[]);

/*
 * Deletes a value from an AVL tree. After deletion,
 * it checks the balance and rebalances it if necessary.
 */
void AVLTreeDelete(AVLTree* tree, const char code[]);

// Deletes a node and all its kids.
void NodeFree(AVLNode* node);

// Deletes a tree.
void FreeAVLTree(AVLTree* tree);