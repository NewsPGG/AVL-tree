#include "../../../src/MainTask/AVL-Tree/AVL-Tree.h"
#include <assert.h>
#include <stdlib.h>

static int checkAVLTree(AVLNode* node) {
    if (node == NULL) {
        return -1;
    }

    int leftHeight = checkAVLTree(node->left);
    int rightHeight = checkAVLTree(node->right);

    if (leftHeight == -1 || rightHeight == -1) {
        return -1;
    }

    int balance = rightHeight - leftHeight;
    if (balance < -1 || balance > 1) {
        return -1;
    }

    int realHeight = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    if (node->height != realHeight) {
        return -1;
    }

    return realHeight;
}

static int isAVLTree(AVLTree* tree) {
    return checkAVLTree(tree->root) != -1;
}

void TestCreateAVLTree() {
    AVLTree* tree = CreateAVLTree();
    assert(tree);
    assert(tree->root);
    FreeAVLTree(tree);
}

void TestInsertOneElementAVLTree() {
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "ABC");
    assert(AVLTreeFind(tree, "ABC"));

    FreeAVLTree(tree);
}

void TestDeleteOneElementAVLTree() {
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "ABC");
    assert(AVLTreeFind(tree, "ABC"));
    AVLTreeDelete(tree, "ABC");
    assert(!AVLTreeFind(tree, "ABC"));

    FreeAVLTree(tree);
}

void TestInsertTenElementsAVLTree() {
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    for (int i = 65; i < 76; i++) {
        char character = (char)i;
        AVLTreeInsert(tree, &character);
        assert(AVLTreeFind(tree, &character));
    }

    FreeAVLTree(tree);
}

void TestDeleteTenElementAVLTree() {
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    for (int i = 65; i < 76; i++) {
        char character = (char)i;
        AVLTreeInsert(tree, &character);
        assert(AVLTreeFind(tree, &character));
        AVLTreeDelete(tree, &character);
        assert(!AVLTreeFind(tree, &character));
    }

    FreeAVLTree(tree);
}

void TestLLBalanceAVLTree() {
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "30");
    AVLTreeInsert(tree, "20");
    AVLTreeInsert(tree, "10");

    assert(isAVLTree(tree));

    FreeAVLTree(tree);
}

void TestLRBalanceAVLTree() {
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "30");
    AVLTreeInsert(tree, "10");
    AVLTreeInsert(tree, "20");

    assert(isAVLTree(tree));

    FreeAVLTree(tree);
}

void TestRRBalanceAVLTree() {
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "10");
    AVLTreeInsert(tree, "20");
    AVLTreeInsert(tree, "30");

    assert(isAVLTree(tree));

    FreeAVLTree(tree);
}

void TestRLBalanceAVLTree() {
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "10");
    AVLTreeInsert(tree, "30");
    AVLTreeInsert(tree, "20");

    assert(isAVLTree(tree));

    FreeAVLTree(tree);
}