#pragma once

typedef struct ListNode {
    char* code;
    char* name;
    int value;
    struct ListNode* next;
} ListNode;

typedef struct List {
    struct ListNode* head;
} List;

/**
 * Create a singly linked list. The head of the list is NULL.
 */
List* newList();

/**
 * Inserts a value into a singly linked list.
 * The element is inserted into the list in lexicographic order.
 * Returns 1 if the insertion is successful, 0 otherwise.
 */
int insert(List* list, const char code[], const char name[]);

/**
 * Removes a value from a singly linked list.
 * Returns 1 if the deletion was successful, 0 otherwise.
 */
int delete(List* list, const char code[]);

/**
 * Finds an element in a singly linked list.
 */
ListNode* find(List* list, const char code[]);

/**
 * Deletes a singly linked list.
 */
void deleteList(List* list);