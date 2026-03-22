#include "../../../src/BonusTask/SingleLinkedList/SingleLinkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void CreateNewLIst()
{
    List* list = newList();
    assert(list);

    deleteList(list);
}

void InsertOneElement()
{
    List* list = newList();
    assert(list);

    assert(insert(list, "one", "one"));
    assert(find(list, "one") != NULL);

    deleteList(list);
}

void DeleteOneElement()
{
    List* list = newList();
    assert(list);

    assert(insert(list, "one", "one"));
    assert(find(list, "one") != NULL);

    assert(delete(list, "one"));
    assert(find(list, "one") == NULL);

    deleteList(list);
}

void InsertTenElements()
{
    List* list = newList();
    assert(list);

    char key[10];
    for (int i = 1; i <= 10; i++) {
        sprintf(key, "%d", i);
        assert(insert(list, key, key));
        assert(find(list, key) != NULL);
    }

    deleteList(list);
}

void DeleteAllElements()
{
    List* list = newList();
    assert(list);

    char keys[10][10];
    for (int i = 1; i <= 10; i++) {
        sprintf(keys[i-1], "%d", i);
        printf("i=%d, key='%s'\n", i, keys[i-1]);
        int res = insert(list, keys[i-1], keys[i-1]);
        printf("insert returned %d\n", res);
        assert(res);
        assert(find(list, keys[i-1]) != NULL);
    }

    for (int i = 1; i <= 10; i++) {
        assert(delete(list, keys[i-1]));
        assert(find(list, keys[i-1]) == NULL);
    }

    deleteList(list);
}

int main() {
    CreateNewLIst();
    InsertOneElement();
    DeleteOneElement();
    InsertTenElements();
    DeleteAllElements();
    return 0;
}