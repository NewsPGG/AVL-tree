#include "SingleLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* newList()
{
    List* list = malloc(sizeof(List));

    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    return list;
}

int insert(List* list, const char code[], const char name[])
{
    if (list == NULL) {
        return 0;
    }

    if (find(list, code)) {
        return 0;
    }

    ListNode* newNode = malloc(sizeof(ListNode));
    if (newNode == NULL) {
        return 0;
    }

    newNode->code = malloc(strlen(code) + 1);
    newNode->name = malloc(strlen(name) + 1);

    if (newNode->code == NULL || newNode->name == NULL) {
        free(newNode->code);
        free(newNode->name);
        free(newNode);
        return 0;
    }

    strcpy(newNode->code, code);
    strcpy(newNode->name, name);
    newNode->next = NULL;

    ListNode* previous = NULL;
    ListNode* current = list->head;

    while (current && strcmp(current->code, code) < 0) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        newNode->next = previous->next;
        previous->next = newNode;
    }

    return 1;
}

int delete(List* list, const char code[])
{
    if (list == NULL || list->head == NULL) {
        return 0;
    }

    ListNode* previous = NULL;
    ListNode* current = list->head;

    while (current && strcmp(current->code, code) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return 0;
    }

    if (previous == NULL) {
        list->head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current->code);
    free(current->name);
    free(current);

    return 1;
}

ListNode* find(List* list, const char code[])
{
    if (list == NULL || list->head == NULL) {
        return NULL;
    }

    ListNode* current = list->head;

    while (current) {
        if (strcmp(current->code, code) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void deleteList(List* list)
{
    if (list == NULL) {
        return;
    }

    ListNode* current = list->head;

    while (current) {
        ListNode* next = current->next;
        free(current->code);
        free(current->name);
        free(current);
        current = next;
    }

    free(list);
}