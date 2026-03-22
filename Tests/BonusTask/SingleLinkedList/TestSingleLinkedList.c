#include "../../../src/BonusTask/SingleLinkedList/SingleLinkedList.h"
#include <assert.h>
#include <stdlib.h>

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

    for (int i = 1; i <= 10; i++) {
        assert(insert(list, "i", "i"));
        assert(find(list, "i") != NULL);
    }

    deleteList(list);
}

void DeleteAllElements()
{
    List* list = newList();
    assert(list);

    for (int i = 1; i <= 10; i++) {
        assert(insert(list, "i", "i"));
        assert(find(list, "i") != NULL);
    }

    for (int i = 1; i <= 10; i++) {
        assert(delete(list, "i"));
        assert(find(list, "i") == NULL);
    }

    deleteList(list);
}