#include "AVL-Tree/AVL-Tree.h"
#include "AVL-Tree/AVL-Tree.c"
#include <stdio.h>
#include <string.h>

static void find(AVLTree* tree, char code[]) {
    AVLNode* airport = AVLTreeFind(tree, code);
    if (airport == NULL) {
        printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
    } else {
        printf("%s → %s\n", airport->code, airport->name);
    }
}

static void add(AVLTree* tree, char codeAndName[]) {
    char* colon = strchr(codeAndName, ':');

    if (colon == NULL) {
        printf("Ошибка: неправильный формат, ожидается код:название\n");
        return;
    }

    *colon = '\0';
    char* code = codeAndName;
    char* name = colon + 1;

    if (strlen(code) == 0 || strlen(name) == 0) {
        printf("Ошибка: код и название не могут быть пустыми\n");
        return;
    }

    if (AVLTreeInsert(tree, code, name)) {
        printf("Аэропорт '%s' добавлен в базу.\n", code);
    } else {
        printf("Аэропорт '%s' уже в базе!\n", code);
    }
}

static void delete(AVLTree* tree, char code[]) {
    if (AVLTreeDelete(tree, code)) {
        printf("Аэропорт '%s' удалён из базы.\n", code);
    } else {
        printf("Аэропорт '%s' не найден в базе!\n", code);
    }
}

static void saveRecursive(AVLNode* node, FILE* f) {
    if (node == NULL) {
        return;
    }

    saveRecursive(node->left, f);
    fprintf(f, "%s:%s\n", node->code, node->name);
    saveRecursive(node->right, f);
}

static int countNodes(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }

    return 1 + countNodes(node->left) + countNodes(node->right);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return -1;
    }

    AVLTree* tree = CreateAVLTree();
    if (tree == NULL) {
        return -1;
    }

    FILE* file = fopen(argv[1], "r");
    int count = 0;
    if (file != NULL) {
        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\r\n")] = '\0';
            char* colon = strchr(line, ':');
            if (colon != NULL) {
                *colon = '\0';
                char* code = line;
                char* name = colon + 1;
                AVLTreeInsert(tree, code, name);
                count++;
            }
        }
        fclose(file);
        printf("Загружено %d аэропортов. Система готова к работе.\n", count);
    } else {
        printf("Файл не найден. Начинаем с пустой базы.\n");
    }

    char input[512];
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\r\n")] = '\0';
        if (strlen(input) == 0) continue;

        char* space = strchr(input, ' ');
        char* cmd = input;
        char* args = NULL;
        if (space != NULL) {
            *space = '\0';
            args = space + 1;
            while (*args == ' ') {
                args++;
            }
        }
        if (strlen(cmd) == 0) continue;

        if (strcmp(cmd, "quit") == 0) {
            break;
        } else if (strcmp(cmd, "find") == 0) {
            if (args == NULL || *args == '\0') {
                printf("Ошибка: укажите код аэропорта\n");
                continue;
            }
            find(tree, args);
        } else if (strcmp(cmd, "add") == 0) {
            if (args == NULL || *args == '\0') {
                printf("Ошибка: укажите код:название\n");
                continue;
            }
            add(tree, args);
        } else if (strcmp(cmd, "delete") == 0) {
            if (args == NULL || *args == '\0') {
                printf("Ошибка: укажите код аэропорта\n");
                continue;
            }
            delete(tree, args);
        } else if (strcmp(cmd, "save") == 0) {
            FILE* out = fopen(argv[1], "w");
            if (out == NULL) {
                printf("Ошибка сохранения: не удалось открыть файл\n");
                continue;
            }
            saveRecursive(tree->root, out);
            fclose(out);
            int total = countNodes(tree->root);
            printf("База сохранена: %d аэропортов.\n", total);
        } else {
            printf("Неизвестная команда: %s\n", cmd);
        }
    }

    FreeAVLTree(tree);
    return 0;
}