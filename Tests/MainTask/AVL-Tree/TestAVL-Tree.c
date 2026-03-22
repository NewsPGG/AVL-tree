#include "../../../src/MainTask/AVL-Tree/AVL-Tree.h"
#include <assert.h>
#include <stdlib.h>

static int checkAVLTree(AVLNode* node)
{
    if (node == NULL) {
        return -1;
    }

    int leftHeight = checkAVLTree(node->left);
    int rightHeight = checkAVLTree(node->right);

    if (leftHeight == -2 || rightHeight == -2) {
        return -2;
    }

    int balance = rightHeight - leftHeight;
    if (balance < -1 || balance > 1) {
        return -2;
    }

    int realHeight = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    if (node->height != realHeight) {
        return -2;
    }

    return realHeight;
}

static int isAVLTree(AVLTree* tree)
{
    return checkAVLTree(tree->root) != -2;
}

void TestCreateAVLTree()
{
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    FreeAVLTree(tree);
}

void TestInsertOneElementAVLTree()
{
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "ABC", "Hello World");
    assert(AVLTreeFind(tree, "ABC"));

    FreeAVLTree(tree);
}

void TestDeleteOneElementAVLTree()
{
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "ABC", "Hello World");
    assert(AVLTreeFind(tree, "ABC"));
    AVLTreeDelete(tree, "ABC");
    assert(!AVLTreeFind(tree, "ABC"));

    FreeAVLTree(tree);
}

void TestInsertTenElementsAVLTree()
{
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    for (int i = 65; i < 76; i++) {
        char key[2] = { (char)i, '\0' };
        char val[2] = { (char)i, '\0' };
        AVLTreeInsert(tree, key, val);
        assert(AVLTreeFind(tree, key));
    }

    FreeAVLTree(tree);
}

void TestDeleteTenElementAVLTree()
{
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    for (int i = 65; i < 76; i++) {
        char key[2] = { (char)i, '\0' };
        char val[2] = { (char)i, '\0' };
        AVLTreeInsert(tree, key, val);
        assert(AVLTreeFind(tree, key));
    }

    FreeAVLTree(tree);
}

void TestLLBalanceAVLTree()
{
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "30", "ABC");
    AVLTreeInsert(tree, "20", "BCD");
    AVLTreeInsert(tree, "10", "CDE");

    assert(isAVLTree(tree));

    FreeAVLTree(tree);
}

void TestLRBalanceAVLTree()
{
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "30", "ABC");
    AVLTreeInsert(tree, "10", "BCD");
    AVLTreeInsert(tree, "20", "CDE");

    assert(isAVLTree(tree));

    FreeAVLTree(tree);
}

void TestRRBalanceAVLTree()
{
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "10", "ABC");
    AVLTreeInsert(tree, "20", "BCD");
    AVLTreeInsert(tree, "30", "CDE");

    assert(isAVLTree(tree));

    FreeAVLTree(tree);
}

void TestRLBalanceAVLTree()
{
    AVLTree* tree = CreateAVLTree();
    assert(tree);

    AVLTreeInsert(tree, "10", "ABC");
    AVLTreeInsert(tree, "30", "BCD");
    AVLTreeInsert(tree, "20", "CDE");

    assert(isAVLTree(tree));

    FreeAVLTree(tree);
}

int main()
{
    TestCreateAVLTree();
    TestInsertOneElementAVLTree();
    TestDeleteOneElementAVLTree();
    TestInsertTenElementsAVLTree();
    TestDeleteTenElementAVLTree();
    TestLLBalanceAVLTree();
    TestLRBalanceAVLTree();
    TestRRBalanceAVLTree();
    TestRLBalanceAVLTree();
    return 0;
}